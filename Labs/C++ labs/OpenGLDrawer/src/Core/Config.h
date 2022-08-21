//
// Created by Anton on 17.08.2022.
//

#ifndef GRAPHICS_CONFIG_H
#define GRAPHICS_CONFIG_H

#include <iostream>
#include "../Core/Structures.h"

class Config
{
public:
    static bool Load(const std::string& configPath);
};


#endif //GRAPHICS_CONFIG_H
