//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#define GLEW_STATIC

#include "../OpenGL/include/GLEW/glew.h"
#include "glfw3.h"
#include "string"

//class Window;

class Window
{
private:
    static GLFWwindow * window;
    static int width, height;
public:

    static int init(int w, int h, const std::string& name);
    static void terminate();

    static void setCursorMode(int cursorMode);
    static void setShouldClose(bool shouldClose);
    static bool isShouldClose();
    static void swapBuffers();

    static int getWidth();
    static int getHeight();

    static GLFWwindow * getCurrentWindow();

    static void setWidth(int w);
    static void setHeight(int h);

    static void Tick();
};


#endif //GRAPHICS_WINDOW_H
