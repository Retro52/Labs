#define GLEW_STATIC

/* Default libs */
#include <iostream>
#include <memory>
#include <string>

/* GL libs */
#include "OpenGL/include/GLEW/glew.h"
#include "OpenGL/include/GLFW/glfw3.h"
#include "OpenGL/include/glm/ext.hpp"

/* Custom classes */
#include "general/Camera.h"
#include "general/Window.h"
#include "general/EventsHandler.h"


int main(int argc, char** argv)
{
    /* Program initialization */
    Window::init(1920, 1080, "Lab 4");
    EventsHandler::init();
    /* Creating main camera */
    std::unique_ptr<Camera> camera = std::make_unique<Camera>(glm::vec3(32,32,32), glm::radians(90.0f));

    _sleep(4000);


    /* Terminate program execution through static method, can  also be called by direct reference to mainWindow */
    Window::setShouldClose(true);
}