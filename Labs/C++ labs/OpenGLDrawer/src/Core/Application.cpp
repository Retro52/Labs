//
// Created by Anton on 27.08.2022.
//

#include <chrono>
#include <iostream>
#include "Application.h"
#include "Global.h"


void Application::Create()
{
    auto start = std::chrono::high_resolution_clock::now();

    /* Program initialization */
    try
    {
        Global::Initialize();
        LOG(INFO) << "Program successfully loaded in " << std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::high_resolution_clock::now() - start).count() / 1000.0f << " seconds";
    }
    catch(std::exception& e)
    {
        LOG(ERROR) << "Fatal error. Reason: " << e.what();
        LOG(FATAL) << "Program failed in " << std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::high_resolution_clock::now() - start).count() / 1000.0f << " seconds";
    }
}

int Application::Run()
{
    try
    {
        /* Tick event */
        while (!Window::IsShouldClose())
        {
            /* Global tick events */
            Global::Tick();

            Global::Draw(ResourcesManager::GetPlayerCamera());

            /* Swapping buffers and pulling user inputs */
            Global::EndFrame();
        }
    }
    catch(const std::exception& exp)
    {
        LOG(ERROR) << "Exception caught, terminating program. What: " << exp.what();
        return EXIT_FAILURE;
    }
    Window::Terminate();
    LOG(INFO) << "Window terminated, program finished";
    return EXIT_SUCCESS;
}
