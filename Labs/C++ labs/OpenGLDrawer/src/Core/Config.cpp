//
// Created by Anton on 17.08.2022.
//

#include "Window.h"
#include "Config.h"
#include "ResourcesManager.h"
#include "../Loaders/inipp.h"
#include "../Loaders/json.hpp"
#include "../Logging/easylogging++.h"


bool Config::Load(const std::string &configPath)
{
    int windowHeight, windowWidth;
    bool windowFullScreen;
    std::string windowName, meshesConfigPath, shadersConfigPath;

    std::ifstream is(configPath);

    if (!is.is_open())
    {
        LOG(ERROR) << "Failed to load config, file " << configPath << " not found";
        return false;
    }

    inipp::Ini<char> ini;

    ini.parse(is);
    ini.default_section(ini.sections["DEFAULT"]);
    ini.interpolate();

    inipp::get_value(ini.sections["DEFAULT"], "windowName", windowName);
    inipp::get_value(ini.sections["DEFAULT"], "windowWidth", windowWidth);
    inipp::get_value(ini.sections["DEFAULT"], "windowHeight", windowHeight);
    inipp::get_value(ini.sections["DEFAULT"], "windowFullScreen", windowFullScreen);

    // creating main window
    if(!Window::Initialize(windowWidth, windowHeight, windowName, windowFullScreen))
    {
        LOG(INFO) << "OpenGL was successfully initialized, window created";
    }
    else
    {
        LOG(FATAL) << "Error during OpenGL initialization";
        return false;
    }

    inipp::get_value(ini.sections["SHADERS"], "shadersConfigPath", shadersConfigPath);

    is.close();

    is = std::ifstream (shadersConfigPath);
    if (!is.is_open())
    {
        LOG(ERROR) << "Failed to load .json config, file " << shadersConfigPath << " not found";
        return false;
    }

    json data = json::parse(is);

    for (const auto& shader : data["Shaders"].items())
    {
        ResourcesManager::RegisterShader(shader.key(), shader.value()[0], shader.value()[1]);
    }

    /* TODO: add shader validation */
    for (const auto& model : data["Models"].items())
    {
        LOG(INFO) << "Model data: " << model.key() << "; " << model.value();
        ResourcesManager::RegisterModel(model.key(), model.value());
        LOG(INFO) << "Model " << model.key() << " registered";
    }
    is.close();
    data.clear();
    return true;
}
