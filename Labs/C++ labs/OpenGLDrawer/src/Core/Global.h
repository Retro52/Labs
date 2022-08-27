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
#include "../include/OpenGL/include/glm/glm.hpp"


class Global
{
public:
    /* Restriction to create an instance of this class */
    Global() = delete;
    Global(Global&&) = delete;
    Global(const Global&) = delete;

    /**
     * Load the program
     */
    static void Initialize();

    /**
     * Is being executed every frame
     */
    static void Tick();

    /**
     * Draws the scene
     * @param camera player camera
     */
    static void Draw(const std::unique_ptr<PerspectiveCamera> &camera);

    /**
     * Ends frame by swapping buffers and more
     */
    static void EndFrame();

    /**
     * Get last frame delta time
     * @return delta time, in seconds
     */
    static double GetWorldDeltaTime();
private:
    static long frame;
    static double lastTime, deltaTime, elapsedTime;
    static bool shouldDrawMesh, shouldDrawLights, shouldDrawAxis, shouldDrawOutline;
    static int curFPS, drawMode;
};

#endif //GRAPHICS_GLOBAL_H
