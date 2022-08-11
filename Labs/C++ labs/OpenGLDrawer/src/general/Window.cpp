//
// Created by Anton on 12.12.2021.
//
#define GLEW_STATIC

#include "Window.h"
#include <iostream>

GLFWwindow* Window::window;
int Window::width = 0;
int Window::height = 0;

/**
 * Initializes OpenGL libraries and creates a window
 * @param w window width
 * @param h window height
 * @param name window name
 * @return exit status
 */
int Window::init(int w, int h, const std::string &name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    Window::window = glfwCreateWindow(w, h, name.c_str(), nullptr, nullptr);

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
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    Window::width = w;
    Window::height = h;
    return 0;
}

/**
 * Terminates a window
 */
void Window::terminate()
{
    glfwTerminate();
}

/**
 * Changes cursor mode
 * @param cursorMode new cursor mode
 */
void Window::setCursorMode(int cursorMode)
{
    glfwSetInputMode(Window::window, GLFW_CURSOR, cursorMode);
}

/**
 * Returns if glfw should close window
 * @return true if glfw should close window, false otherwise
 */
bool Window::isShouldClose()
{
    return glfwWindowShouldClose(Window::window);
}

/**
 * Tell glfw to/not to close window
 * @param shouldClose true if window should be closed
 */
void Window::setShouldClose(bool shouldClose)
{
    glfwSetWindowShouldClose(Window::window, shouldClose);
}

/**
 * Update buffers
 */
void Window::swapBuffers()
{
    glfwSwapBuffers(Window::window);
}

/**
 * Get current window width
 * @return window width
 */
int Window::getWidth()
{
    return Window::width;
}

/**
 * Get current window height
 * @return window height
 */
int Window::getHeight()
{
    return Window::height;
}

/**
 * Set new window width
 * @param w new window width in pixels
 */
void Window::setWidth(int w)
{
    if (400 < w && w < 3840)
    {
        Window::width = w;
    }
}

/**
 * Set new window height
 * @param h new window height in pixels
 */
void Window::setHeight(int h)
{
    if (400 < h && h < 2160)
    {
        Window::height = h;
    }
}

/**
 * Get current glfw window
 * @return
 */
GLFWwindow * Window::getCurrentWindow()
{
    return Window::window;
}

