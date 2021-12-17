//
// Created by Anton on 14.12.2021.
//

#include <sstream>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include "objLoader.h"

void objLoader::loadObjModel(const char *objFileName, std::vector<float> &array)
{
    std::ifstream ifs(objFileName);

    auto * tempModel = new objLoader;
    std::stringstream ssFileContent;
    std::string temp;
    std::string line;
    std::vector<float> result;
    while (std::getline(ifs, line))
    {
        ssFileContent << line;
        if (!line.empty())
        {
            if (line[0] == 'v')
            {
                std::stringstream ssOneLine(line);
                if (line[1] == 't')
                {
                    ssOneLine >> temp;
                    Float3 tempTexcoord{};
                    ssOneLine >> tempTexcoord.Data[0]
                              >> tempTexcoord.Data[1];
                    tempTexcoord.Data[2] = 0;
                    tempModel->texcoord.push_back(tempTexcoord);
                }
                if (line[1] == 'n')
                {
                    ssOneLine >> temp;
                    Float3 tempNormal{};
                    ssOneLine >> tempNormal.Data[0] >> tempNormal.Data[1] >> tempNormal.Data[2];
                    tempModel->normal.push_back(tempNormal);
                }
                {
                    ssOneLine >> temp;
                    Float3 tempLocation{};
                    ssOneLine >> tempLocation.Data[0] >> tempLocation.Data[1] >> tempLocation.Data[2];
                    tempModel->position.push_back(tempLocation);
                }
            }
            else if (line[0] == 'f')
            {
                std::stringstream ssOneLine(line);
                ssOneLine >> temp;
                if (std::count(line.begin(), line.end(), '/') > 9)
                {
                    std::cerr << "[WARNING]::OBJLOADER Mesh "
                    << objFileName
                    << " faces were not triangulated, visual problems expected:\n"
                    <<"Not triangulated faces:\n"
                    << line
                    << std::endl;
                }
                std::string vertexStr;
                Face tempFace{};
                for (auto &i : tempFace.vertex)
                {
                    ssOneLine >> vertexStr;
                    size_t pos = vertexStr.find_first_of('/');
                    std::string locIndexStr = vertexStr.substr(0, pos);
                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texIndexSrt = vertexStr.substr(pos + 1, pos2 - 1 - pos);
                    std::string norIndexSrt = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
                    i[0] = std::stoi(locIndexStr);
                    i[1] = std::stoi(texIndexSrt);
                    i[2] = std::stoi(norIndexSrt);
                }
                tempModel->face.push_back(tempFace);
            }
        }
    }
    for(auto &pos : tempModel->face)
    {
        for(auto & i : pos.vertex)
        {
            result.push_back(tempModel->position[i[0] - 1].Data[0]);
            result.push_back(tempModel->position[i[0] - 1].Data[1]);
            result.push_back(tempModel->position[i[0] - 1].Data[2]);
            result.push_back(tempModel->texcoord[i[1] - 1].Data[0]);
            result.push_back(tempModel->texcoord[i[1] - 1].Data[1]);
            result.push_back(tempModel->normal[i[2] - 1].Data[0]);
            result.push_back(tempModel->normal[i[2] - 1].Data[1]);
            result.push_back(tempModel->normal[i[2] - 1].Data[2]);
        }
    }
    delete tempModel;
    array = std::vector<float>(result);
}
