//
// Created by Anton on 14.08.2022.
//

#ifndef GRAPHICS_GLOBAL_H
#define GRAPHICS_GLOBAL_H

#include <iostream>
#include "Window.h"
#include "EventsHandler.h"
#include "ThreadSafeQueue.h"
#include "PerspectiveCamera.h"
#include "../draw/Shader.h"
#include "../logging/easylogging++.h"
#include "../OpenGL/include/glm/glm.hpp"


class Global
{
private:
    static double lastTime, deltaTime;
    static bool shouldDrawMesh, shouldDrawLights, shouldDrawAxis, shouldDrawOutline;
    static std::shared_ptr<Mesh> cube, sphere;
    static std::shared_ptr<Material> defaultMaterial;
    static std::shared_ptr<Shader> mainShader, lightShader, outlineShader, axisShader;
    static int LoadMeshes();
    static int LoadShaders();
    static int LoadMaterials();
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
