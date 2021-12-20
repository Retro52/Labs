//
// Created by Anton on 12.12.2021.
//

#include "EventsHandler.h"
#include "EventsHandlerFields.h"
#include "Window.h"
#include <memory>
#include <cstring>

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (EventsHandler::_cursor_started)
    {
        EventsHandler::deltaX += (float) xpos - EventsHandler::x;
        EventsHandler::deltaY += (float) ypos - EventsHandler::y;
    }
    else
    {
        EventsHandler::_cursor_started = true;
    }
    EventsHandler::x = (float) xpos;
    EventsHandler::y = (float) ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        EventsHandler::_keys[_MOUSE_BUTTONS_OFFSET + button] = true;
        EventsHandler::_frames[_MOUSE_BUTTONS_OFFSET + button] = EventsHandler::_current;
    }
    else if (action == GLFW_RELEASE)
    {
        EventsHandler::_keys[_MOUSE_BUTTONS_OFFSET + button] = false;
        EventsHandler::_frames[_MOUSE_BUTTONS_OFFSET + button] = EventsHandler::_current;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        EventsHandler::_keys[key] = true;
        EventsHandler::_frames[key] = EventsHandler::_current;
    }
    else if (action == GLFW_RELEASE)
    {
        EventsHandler::_keys[key] = false;
        EventsHandler::_frames[key] = EventsHandler::_current;
    }
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
    Window::setHeight(height);
    Window::setWidth(width);
}

int EventsHandler::init()
{
    GLFWwindow * window = Window::getCurrentWindow();
    EventsHandler::_keys = std::make_unique<bool[]>(1032);
    EventsHandler::_frames = std::make_unique<uint[]>(1032);
    std::memset(_keys.get(), false, 1032*sizeof(bool));
    std::memset(_frames.get(), 0, 1032*sizeof(uint));

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    return 0;
}

bool EventsHandler::pressed(int keycode)
{
    if (keycode < 0 || keycode >= _MOUSE_BUTTONS_OFFSET)
    {
        return false;
    }
    return _keys[keycode];
}

bool EventsHandler::justPressed(int keycode)
{
    if (keycode < 0 || keycode >= _MOUSE_BUTTONS_OFFSET)
    {
        return false;
    }
    return _keys[keycode] && _frames[keycode] == _current;
}

bool EventsHandler::clicked(int button)
{
    int index = _MOUSE_BUTTONS_OFFSET + button;
    return _keys[index];
}

bool EventsHandler::justClicked(int button)
{
    int index = _MOUSE_BUTTONS_OFFSET + button;
    return _keys[index] && _frames[index] == _current;
}

void EventsHandler::toggleCursor()
{
    _cursor_locked = !_cursor_locked;
    Window::setCursorMode(_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void EventsHandler::pullEvents()
{
    _current++;
    deltaX = 0.0f;
    deltaY = 0.0f;
    glfwPollEvents();
}