#define GLEW_STATIC

/* TODO: create a namespace for the project*/

/* Default libs */
#include <future>

/* GL libs */

/* Custom classes */
#include "Core/PerspectiveCamera.h"
#include "Core/Window.h"
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
    auto start = std::chrono::high_resolution_clock::now();

    /* Program initialization */
    if (!Global::Initialize())
    {
        auto stop = std::chrono::high_resolution_clock::now();
        LOG(INFO) << "Program successfully loaded in " << std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(stop - start).count() / 1000.0f << " seconds";
    }
    else
    {
        auto stop = std::chrono::high_resolution_clock::now();
        LOG(FATAL) << "Program failed in " << std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(stop - start).count() / 1000.0f << " seconds";
    }

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
