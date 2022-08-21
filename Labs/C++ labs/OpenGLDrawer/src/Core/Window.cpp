//
// Created by Anton on 12.12.2021.
//
#define GLEW_STATIC

#include "Window.h"
#include "EventsHandler.h"
#include <iostream>

GLFWwindow * Window::window;
int Window::width = 0;
int Window::height = 0;


int Window::Initialize(int w, int h, const std::string &name, bool fullScreen)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    if (fullScreen)
    {
        Window::window = glfwCreateWindow(w, h, name.c_str(), glfwGetPrimaryMonitor(), nullptr);
    }
    else
    {
        Window::window = glfwCreateWindow(w, h, name.c_str(), nullptr, nullptr);
    }

    if (Window::window == nullptr)
    {
        std::cerr << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(Window::window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, w, h);
    glClearColor(0.0f,0.0f,0.0f,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glfwSwapInterval(0);
    Window::width = w;
    Window::height = h;
    return 0;
}

void Window::terminate()
{
    glfwTerminate();
}

void Window::setCursorMode(int cursorMode)
{
    glfwSetInputMode(Window::window, GLFW_CURSOR, cursorMode);
}

bool Window::isShouldClose()
{
    return glfwWindowShouldClose(Window::window);
}

void Window::setShouldClose(bool shouldClose)
{
    glfwSetWindowShouldClose(Window::window, shouldClose);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(Window::window);
}

int Window::getWidth()
{
    return Window::width;
}

int Window::getHeight()
{
    return Window::height;
}

void Window::setWidth(int w)
{
    if (400 < w && w < 3840)
    {
        Window::width = w;
    }
}

void Window::setHeight(int h)
{
    if (400 < h && h < 2160)
    {
        Window::height = h;
    }
}

GLFWwindow * Window::getCurrentWindow()
{
    return Window::window;
}

void Window::Tick()
{
    if (EventsHandler::justPressed(GLFW_KEY_ESCAPE))
    {
        Window::setShouldClose(true);
    }
    /* Show/hide cursor */
    if (EventsHandler::justPressed(GLFW_KEY_TAB))
    {
        EventsHandler::toggleCursor();
    }
}

void Window::Update()
{
    glfwSetWindowSize(window, width, height);
}

