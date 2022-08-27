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
    EventsHandler() = delete;
    EventsHandler(EventsHandler&&) = delete;
    EventsHandler(const EventsHandler&) = delete;

    /**
     * Initializes event handler and sets callbacks for actions
     * @return exit code
     */
    static int Initialize();

    /**
     * UpdateModelMatrix all events, called once every frame
     */
    static void PullEvents();

    /**
     * Check if key is pressed
     * @param keycode key id
     * @return true if pressed, false otherwise
     */
    static bool IsPressed(int keycode);

    /**
     * Chek if key was just pressed
     * @param keycode key id
     * @return true if was just pressed, false otherwise
     */
    static bool IsJustPressed(int keycode);

    /**
     * Check if mouse button is clicked
     * @param button button id
     * @return true if is clicked, false otherwise
     */
    static bool IsClicked(int button);

    /**
     * Check if mouse button was just clicked
     * @param button button id
     * @return true if was just clicked, false otherwise
     */
    static bool IsJustClicked(int button);

    /**
     * Switch hide & show cursor modes
     */
    static void ToggleCursor();

    static std::unique_ptr<bool[]> _keys;
    static std::unique_ptr<uint[]> _frames;
    static uint _current;
};


#endif //GRAPHICS_EVENTSHANDLER_H
