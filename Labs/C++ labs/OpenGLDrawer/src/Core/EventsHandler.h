//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_EVENTSHANDLER_H
#define GRAPHICS_EVENTSHANDLER_H
#define GLEW_STATIC

#include <memory>
#include "glew.h"
#include "glfw3.h"

typedef unsigned int uint;

class EventsHandler;

class EventsHandler
{
public:
    static float deltaX;
    static float deltaY;
    static float x;
    static float y;
    static bool _cursor_locked;
    static bool _cursor_started;

    /* Restriction to create an instance of this class */
    EventsHandler() = default;

    static int init();
    static void pullEvents();

    static bool pressed(int keycode);
    static bool justPressed(int keycode);

    static bool clicked(int button);
    static bool justClicked(int button);

    static void toggleCursor();

    static std::unique_ptr<bool[]> _keys;
    static std::unique_ptr<uint[]> _frames;
    static uint _current;
};


#endif //GRAPHICS_EVENTSHANDLER_H
