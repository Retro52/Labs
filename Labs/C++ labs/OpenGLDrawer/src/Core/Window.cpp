//
// Created by Anton on 12.12.2021.
//
#define GLEW_STATIC

#include "Window.h"
#include "EventsHandler.h"
#include "InGameException.h"
#include <iostream>

GLFWwindow * Window::window;
int Window::width = 0;
int Window::height = 0;


void Window::Initialize(int w, int h, const std::string &name, bool fullScreen)
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
        throw InGameException("Failure during GLFW window creation");
    }

    glfwMakeContextCurrent(Window::window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        throw InGameException("Failure during GLEW initialization");
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
}

void Window::Terminate()
{
    glfwTerminate();
}

void Window::SetCursorMode(int cursorMode)
{
    glfwSetInputMode(Window::window, GLFW_CURSOR, cursorMode);
}

bool Window::IsShouldClose()
{
    return glfwWindowShouldClose(Window::window);
}

void Window::SetShouldClose(bool shouldClose)
{
    glfwSetWindowShouldClose(Window::window, shouldClose);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(Window::window);
}

int Window::GetWidth()
{
    return Window::width;
}

int Window::GetHeight()
{
    return Window::height;
}

void Window::SetWidth(int w)
{
    if (400 < w && w < 3840)
    {
        Window::width = w;
    }
}

void Window::SetHeight(int h)
{
    if (400 < h && h < 2160)
    {
        Window::height = h;
    }
}

GLFWwindow * Window::GetCurrentWindow()
{
    return Window::window;
}

void Window::Tick()
{
    if (EventsHandler::IsJustPressed(GLFW_KEY_ESCAPE))
    {
        Window::SetShouldClose(true);
    }
    /* Show/hide cursor */
    if (EventsHandler::IsJustPressed(GLFW_KEY_TAB))
    {
        EventsHandler::ToggleCursor();
    }
}

void Window::Update()
{
    glfwSetWindowSize(window, width, height);
}

