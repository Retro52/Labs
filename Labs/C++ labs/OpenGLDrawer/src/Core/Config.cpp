//
// Created by Anton on 17.08.2022.
//

#include "Window.h"
#include "Config.h"
#include "ResourcesManager.h"
#include "../Loaders/inipp.h"
#include "../Loaders/json.hpp"
#include "../Logging/easylogging++.h"
#include "../UI/UIHandler.h"


int Config::Load(const std::string &configPath)
{
    int windowHeight, windowWidth, defaultFontSize;
    bool windowFullScreen;
    std::string windowName, shadersConfigPath, defaultFontPath;

    std::ifstream is(configPath);

    if (!is.is_open())
    {
        LOG(ERROR) << "Failed to load config, file " << configPath << " not found";

        windowWidth = 600;
        windowHeight = 400;
        windowFullScreen = false;
        windowName = "OpenGL Drawer";

        defaultFontSize = 16;
        defaultFontPath = "../res/fonts/arial/arial.ttf";

        shadersConfigPath = "config.json";
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

    std::cerr << windowWidth << "; " << windowHeight << "; "  << windowName << "; "  << windowFullScreen << ";\n";

    // creating main window
    if(!Window::Initialize(windowWidth, windowHeight, windowName, windowFullScreen))
    {
        LOG(INFO) << "OpenGL was successfully initialized, window created";
    }
    else
    {
        LOG(ERROR) << "Failure during OpenGL initialization";
        return -1;
    }

    if(!UIHandler::Initialize(defaultFontPath, defaultFontSize))
    {
        LOG(INFO) << "UI handler successfully initialized";
    }
    else
    {
        LOG(ERROR) << "UI handler was not initialized";
        return -2;
    }

    is = std::ifstream (shadersConfigPath);
    if (!is.is_open())
    {
        LOG(ERROR) << "Failed to open config file '" << shadersConfigPath << "'";
        return -3;
    }

    json data = json::parse(is);

    for (const auto& shader : data["Shaders"].items())
    {
        ResourcesManager::RegisterShader(shader.key(), shader.value()[0], shader.value()[1]);
    }

    /* TODO: add shader validation */
    for (const auto& model : data["Models"].items())
    {
        std::string path = std::string(model.value());
        std::string directory = path.substr(0, path.find_last_of('/'));
        LOG(INFO) << "Model data: " << model.key() << "; " << model.value();
        ResourcesManager::RegisterModel(model.key(), model.value());
        LOG(INFO) << "Model " << model.key() << " registered";
    }
    is.close();
    data.clear();
    return 0;
}
