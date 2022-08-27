//
// Created by Anton on 17.08.2022.
//

#include "Window.h"
#include "Config.h"
#include "ResourcesManager.h"
#include "InGameException.h"
#include "../Loaders/inipp.h"
#include "../Loaders/json.hpp"
#include "../Logging/easylogging++.h"
#include "../UI/UIHandler.h"


void Config::LoadIni(const std::string &configPath)
{
    LOG(INFO) << "Start loading "<< configPath << " file";
    int windowHeight, windowWidth, defaultFontSize;
    bool windowFullScreen;
    std::string windowName, shadersConfigPath, defaultFontPath;

    std::ifstream is(configPath);

    /* TODO: check of this even makes sense */
    /* Set variables to default values */
    windowWidth = 1200;
    windowHeight = 900;
    windowFullScreen = false;
    windowName = "OpenGL Drawer";

    defaultFontSize = 16;
    defaultFontPath = "../res/fonts/arial/arial.ttf";

    shadersConfigPath = "config.json";

    if (!is.is_open())
    {
        LOG(ERROR) << "Failed to load config, file " << configPath << " not found";
        throw InGameException(".ini config file not found");
    }

    else
    {
        inipp::Ini<char> ini;

        ini.parse(is);
        ini.default_section(ini.sections["DEFAULT"]);
        ini.interpolate();

        inipp::get_value(ini.sections["DEFAULT"], "windowName", windowName);
        inipp::get_value(ini.sections["DEFAULT"], "windowWidth", windowWidth);
        inipp::get_value(ini.sections["DEFAULT"], "windowHeight", windowHeight);
        inipp::get_value(ini.sections["DEFAULT"], "windowFullScreen", windowFullScreen);
        inipp::get_value(ini.sections["DEFAULT"], "defaultFontSize", defaultFontSize);
        inipp::get_value(ini.sections["DEFAULT"], "defaultFontPath", defaultFontPath);

        windowWidth = windowWidth > 399 ? windowWidth : 400;
        windowHeight = windowHeight > 399 ? windowHeight : 400;

        inipp::get_value(ini.sections["SHADERS"], "shadersConfigPath", shadersConfigPath);

        is.close();
    }

    LOG(INFO) << configPath << " successfully loaded";
    /* All the exceptions are handled in Global::Init method */
    Window::Initialize(windowWidth, windowHeight, windowName, windowFullScreen);
    UIHandler::Initialize(defaultFontPath, defaultFontSize);
    Config::LoadJson(shadersConfigPath);
}

void Config::LoadJson(const std::string &jsonConfigPath)
{
    LOG(INFO) << "Start loading " << jsonConfigPath << " config file";
    std::ifstream is(jsonConfigPath);
    if (!is.is_open())
    {
        LOG(ERROR) << "Failed to open config file '" << jsonConfigPath << "'";
        throw InGameException("Failed to load .json config file");
    }

    json data = json::parse(is);

    if (data.empty())
    {
        LOG(ERROR) << "Json config file '" << jsonConfigPath << "' is empty";
        throw InGameException("Json file is empty");
    }
    for (const auto& shader : data["Shaders"].items())
    {
        if(!shader.value()[2].is_null())
        {
            ResourcesManager::RegisterShader(shader.key(), shader.value()[0], shader.value()[1], shader.value()[2]);
        }
        else
        {
            ResourcesManager::RegisterShader(shader.key(), shader.value()[0], shader.value()[1]);
        }
    }
    LOG(INFO) << "Shaders loaded";
    for (const auto& model : data["Models"].items())
    {
        std::string path = std::string(model.value());
        std::string directory = path.substr(0, path.find_last_of('/'));
        LOG(INFO) << "Model data: " << model.key() << "; " << model.value();
        ResourcesManager::RegisterModel(model.key(), model.value());
    }
    LOG(INFO) << "Models loaded";

    is.close();
    data.clear();
}
