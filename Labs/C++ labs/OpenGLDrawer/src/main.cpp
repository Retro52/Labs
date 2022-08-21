#define GLEW_STATIC

/* TODO: create a namespace for the project*/

/* Default libs */
#include <future>

/* GL libs */

/* Custom classes */
#include "Core/PerspectiveCamera.h"
#include "Core/Window.h"
#include "Core/EventsHandler.h"
#include "Core/ResourcesManager.h"
#include "Core/Global.h"


/* TODO: replace functions with custom class with static methods like Tick(), Events(), etc. */
/* TODO: rework material class */
/* TODO: create exceptions system */
/* TODO: default loading system, maybe files for ex. */
/* TODO: add comments doxygen-style */

#include <ft2build.h>
#include FT_FREETYPE_H

INITIALIZE_EASYLOGGINGPP;

/**
 * Program entry point
 * @param argc command-line arguments count
 * @param argv command-line arguments
 * @return exit code
 */
int main(int argc, char ** argv)
{
    /* Program initialization */
    Global::Initialize();
    LOG(INFO) << "Default settings successfully initialized";

    /* Rotation set up */
    glm::vec3 rotationAxisX(1, 0, 0), rotationAxisY(0, 0, 1), rotationAxisZ(0, 1, 0), currentRotationAxis(0, 1, 0), lightColor(1, 1, 1);

    /* Hide mouse cursor */
    EventsHandler::toggleCursor();

    LOG(INFO) << "Program successfully loaded";
    /* Tick event */
    while (!Window::isShouldClose())
    {
        /* Global tick events */
        Global::Tick();

        Global::Draw(ResourcesManager::GetPlayerCamera());

        /* Swapping buffers and pulling user inputs */
        Global::EndFrame();
    }
    Window::terminate();
    LOG(INFO) << "Window terminated, program finished";
}
