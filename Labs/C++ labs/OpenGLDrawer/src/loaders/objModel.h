//
// Created by Anton on 14.12.2021.
//

#ifndef GRAPHICS_OBJMODEL_H
#define GRAPHICS_OBJMODEL_H

#include "../general/Structures.h"
#include <iostream>
#include <vector>

class objModel :public List
{
public:
    objModel() {}
    std::vector<float> loadObjModel (const char *); // Загрузить файл модели obj
    void objDraw (); // Рисуем модель obj
public:
    std::vector <Float3> normal, texcoord, position; // В векторном контейнере хранятся нормали, координаты текстуры и информация о положении точки
    std::vector <Face> face; // Сохраняем информацию о лице
    int vertnum; // Количество точек хранения
    int coordnum; // хранит количество текстурных координат
    std::vector<float> draw;
};

#endif //GRAPHICS_OBJMODEL_H
