//
// Created by Anton on 14.08.2022.
//

#ifndef GRAPHICS_GLOBAL_H
#define GRAPHICS_GLOBAL_H

#include <iostream>
#include "Window.h"
#include "EventsHandler.h"
#include "ResourcesManager.h"
#include "PerspectiveCamera.h"
#include "../Render/Shader.h"
#include "../Logging/easylogging++.h"
#include "../OpenGL/include/glm/glm.hpp"


class Global
{
private:
    static long frame;
    static double lastTime, deltaTime, elapsedTime;
    static bool shouldDrawMesh, shouldDrawLights, shouldDrawAxis, shouldDrawOutline;
    static int curFPS, drawMode;
public:
    static void Initialize();
    static void Tick();
    static void Load(const std::string &path);
    static void Draw(const std::unique_ptr<PerspectiveCamera> &camera);
    static void EndFrame();
    static double GetWorldDeltaTime();
//    std::shared_ptr<Shader> GetShader();
};

#endif //GRAPHICS_GLOBAL_H
