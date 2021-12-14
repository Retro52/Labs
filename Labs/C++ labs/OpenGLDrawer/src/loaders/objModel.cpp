//
// Created by Anton on 14.12.2021.
//

#define GLEW_STATIC
#include "../OpenGL/include/GLEW/glew.h"

#include <sstream>
#include <cstring>
#include <vector>
#include <fstream>
#include "objModel.h"

std::vector<float> objModel::loadObjModel(const char* objFileName)
{
    std::ifstream ifs(objFileName);

    auto * tempModel = new objModel;
    std::stringstream ssFileContent; // Потоковое чтение содержимого файла
    std::string temp; // Принимаем неактуальную информацию
    std::string line;
    std::vector<float> result;
    while (std::getline(ifs, line))
    {
        ssFileContent << line;
        if (!line.empty()) // строка не пустая
        {
            if (line[0] == 'v') // данные, начинающиеся с v
            {
                std::stringstream ssOneLine(line); // Данные хранятся в потоке для легкого назначения
                if (line[1] == 't') // Информация о текстуре
                {
                    ssOneLine >> temp; // Принять идентификатор vt
                    Float3 tempTexcoord;
                    ssOneLine >> tempTexcoord.Data[0]
                              >> tempTexcoord.Data[1]; // Данные хранятся во временных переменных
                    tempTexcoord.Data[2] = 0;
                    tempModel->texcoord.push_back(tempTexcoord); // Сохранить в контейнере
                }
                if (line[1] == 'n') // нормальная информация
                {
                    ssOneLine >> temp; // получить идентификатор vn
                    Float3 tempNormal;
                    ssOneLine >> tempNormal.Data[0] >> tempNormal.Data[1] >> tempNormal.Data[2];
                    tempModel->normal.push_back(tempNormal);
                }
                //еще // информация о местоположении точки
                {
                    ssOneLine >> temp;
                    Float3 tempLocation;
                    ssOneLine >> tempLocation.Data[0] >> tempLocation.Data[1] >> tempLocation.Data[2];
                    tempModel->position.push_back(tempLocation);
                }
            } else if (line[0] == 'f') // информация об области
            {
                std::stringstream ssOneLine(line); // Поток читает одну строку данных
                ssOneLine >> temp; // получить идентификатор f
                // f информация exp: f 1/1/1 2/2/2 3/3/3 индекс позиции / индекс текстуры / треугольник с нормальным индексом три точки образуют поверхность
                std::string vertexStr; // Получение содержимого потока
                Face tempFace;
                for (auto &i : tempFace.vertex) // три точки на грани
                {
                    ssOneLine >> vertexStr; // Считать информацию индекса точки из потока
                    size_t pos = vertexStr.find_first_of('/'); // найти позицию первого /
                    std::string locIndexStr = vertexStr.substr(0, pos); // Информация о положении точки назначения
                    size_t pos2 = vertexStr.find_first_of('/', pos +
                                                               1); // найти второе / то есть найти информацию о координатах текстуры точки
                    std::string texIndexSrt = vertexStr.substr(pos + 1, pos2 - 1 -
                                                                        pos); // Информация о координатах текстуры точки назначения
                    std::string norIndexSrt = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 -
                                                                         pos2); // Нормальная информация о точке назначения
                    i[0] = atof(
                            locIndexStr.c_str()); // Преобразовать информацию индекса из srting в int // Позиционировать информацию индекса позиции
                    i[1] = atof(texIndexSrt.c_str()); // Присвоение информации об индексе координат текстуры
                    i[2] = atof(norIndexSrt.c_str()); // Назначить нормальную информацию
                }
                tempModel->face.push_back(tempFace);
            } else if (line[0] == '#') // Обработка содержимого комментария
            {
                std::stringstream ssOneLine(line); // Поток читает одну строку данных
                ssOneLine >> temp; // receive #
                std::string numtemp;
                while (ssOneLine) {
                    ssOneLine >> temp;
                    if (temp == "faces") {
                        PushBack(tempModel);
                        tempModel = new objModel;
                        break;
                    } else if (temp == "vertices") {
                        tempModel->vertnum = atoi(numtemp.c_str());
                        break;
                    } else if (temp == "texture") {
                        tempModel->coordnum = atoi(numtemp.c_str());
                        break;
                    }
                    numtemp = temp;
                }
            }
        }
    }
    for(auto &pos : tempModel->position)
    {
        pos.display("Position");
    }
    for(auto &pos : tempModel->texcoord)
    {
        pos.display("TextureCoords");
    }
    for(auto &pos : tempModel->normal)
    {
        pos.display("Normals");
    }
    for(auto &pos : tempModel->face)
    {
        pos.display();
        tempModel->position[pos.vertex[0][0] - 1].display("Face position 1");
        tempModel->position[pos.vertex[1][0] - 1].display("Face position 2");
        tempModel->position[pos.vertex[2][0] - 1].display("Face position 3");
        tempModel->texcoord[pos.vertex[0][1] - 1].display("UV position 1");
        tempModel->texcoord[pos.vertex[1][1] - 1].display("UV position 2");
        tempModel->texcoord[pos.vertex[2][1] - 1].display("UV position 2");

        for(auto & i : pos.vertex)
        {
            result.push_back(tempModel->position[i[0] - 1].Data[0]);
            result.push_back(tempModel->position[i[0] - 1].Data[1]);
            result.push_back(tempModel->position[i[0] - 1].Data[2]);
            result.push_back(tempModel->texcoord[i[1] - 1].Data[0]);
            result.push_back(tempModel->texcoord[i[1] - 1].Data[1]);
        }
    }
    for(int j = 0; j < result.size(); j += 5)
    {
        std::cout << "Next coords: " << std::endl;
        std::cout << result[j] << "; ";
        std::cout << result[j + 1] << "; ";
        std::cout << result[j + 2] << "; ";
        std::cout << result[j + 3] << "; ";
        std::cout << result[j + 4] << "; ";
        std::cout << std::endl;
    }
    std::cout << result.size() << std::endl;
    std::cout << "Vertnum: " << tempModel->vertnum << "; Coordnum: " << tempModel->coordnum << std::endl;
//    system("pause");
    delete tempModel;
    return result;
}

void objModel::objDraw()
{
    if (!position.empty())
    {
        int vnum = 0;
        int cnum = 0;
        glBegin(GL_TRIANGLES);
        for (auto & i : face) // цикл через информацию о лице
        {

            // Нормаль, текстура и информация о положении первой точки
            glNormal3fv(normal[i.vertex[0][2] - 1 - vnum].Data);
            glTexCoord2fv(texcoord[i.vertex[0][1] - 1 - cnum].Data);
            glVertex3fv(position[i.vertex[0][0] - 1 - vnum].Data);
            // Нормаль, текстура и информация о положении второй точки
            glNormal3fv(normal[i.vertex[1][2] - 1 - vnum].Data);
            glTexCoord2fv(texcoord[i.vertex[1][1] - 1 - cnum].Data);
            glVertex3fv(position[i.vertex[1][0] - 1 - vnum].Data);
            // Нормальная третья точка, текстура и информация о положении
            glNormal3fv(normal[i.vertex[2][2] - 1 - vnum].Data);
            glTexCoord2fv(texcoord[i.vertex[2][1] - 1 - cnum].Data);
            glVertex3fv(position[i.vertex[2][0] - 1 - vnum].Data);
            vnum += vertnum;
            cnum += coordnum;
        }
        glEnd();
        vnum = 0;
        cnum = 0;
    }

    if (Next<objModel>() != nullptr)
    {
        Next<objModel>()->objDraw();
    }
    else
        return;
}