//
// Created by Anton on 14.12.2021.
//

#ifndef GRAPHICS_OBJLOADER_H
#define GRAPHICS_OBJLOADER_H

#include "../general/Structures.h"
#include <iostream>
#include <vector>

class objLoader : public List
{
public:
    objLoader() = default;
    static void loadObjModel(const char *objFileName, std::vector<float> &array);
public:
    std::vector <Float3> normal, texcoord, position;
    std::vector <Face> face;
    std::vector<float> draw;
};

#endif //GRAPHICS_OBJLOADER_H
