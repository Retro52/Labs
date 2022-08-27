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
    /* Restriction to create an instance of this class */
    Config() = delete;
    Config(Config&&) = delete;
    Config(const Config&) = delete;

    /**
     * Load default .ini config file
     * @param configPath path to the .ini file
     */
    static void LoadIni(const std::string& configPath);

    /**
     * Load default .json file
     * @param jsonConfigPath path to the json file, extracted from .ini file
     */
    static void LoadJson(const std::string& jsonConfigPath);
};


#endif //GRAPHICS_CONFIG_H
