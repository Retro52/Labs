//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#define GLEW_STATIC

#include "../include/OpenGL/include/GLEW/glew.h"
#include "../include/OpenGL/include/GLFW/glfw3.h"
#include "string"

class Window
{
private:
    static GLFWwindow * window;
    static int width, height;
public:
    /* Restriction to create an instance of this class */
    Window() = delete;
    Window(Window&&) = delete;
    Window(const Window&) = delete;

    /**
     * Creates window by given parameters
     * @param w window width
     * @param h window height
     * @param name window name
     * @param fullScreen true if full screen, false otherwise
     */
    static void Initialize(int w, int h, const std::string &name, bool fullScreen);

    /**
     * Terminates the window after program is shut
     */
    static void Terminate();

    /**
     * Set cursor mode
     * @param cursorMode gl enum of cursor mode
     */
    static void SetCursorMode(int cursorMode);

    /**
     * Should program close on the next frame
     * @param shouldClose bool var i window should close
     */
    static void SetShouldClose(bool shouldClose);

    /**
     * Is window about to close
     * @return true if yes, false otherwise
     */
    static bool IsShouldClose();

    /**
     * Swap gl window buffers
     */
    static void SwapBuffers();

    /**
     * Get window width
     * @return window current width
     */
    static int GetWidth();

    /**
     * Get window height
     * @return window height
     */
    static int GetHeight();

    /**
     * Get current window
     * @return current window
     */
    static GLFWwindow * GetCurrentWindow();

    /**
     * Set window width
     * @param w new width
     */
    static void SetWidth(int w);

    /**
     * Set window height
     * @param h new height
     */
    static void SetHeight(int h);

    /**
     * Executed every frame
     */
    static void Tick();

    /**
     * Updates window width and height
     */
    static void Update();
};


#endif //GRAPHICS_WINDOW_H
