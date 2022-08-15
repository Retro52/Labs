//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_EVENTSHANDLERFIELDS_H
#define GRAPHICS_EVENTSHANDLERFIELDS_H
#include "EventsHandler.h"

constexpr int _MOUSE_BUTTONS_OFFSET = 1024;

std::unique_ptr<bool[]> EventsHandler::_keys;
std::unique_ptr<uint[]> EventsHandler::_frames;
uint EventsHandler::_current = 0;
float EventsHandler::deltaX = 0.0F;
float EventsHandler::deltaY = 0.0F;
float EventsHandler::x = 0.0F;
float EventsHandler::y = 0.0F;
bool EventsHandler::_cursor_locked = false;
bool EventsHandler::_cursor_started = false;

#endif //GRAPHICS_EVENTSHANDLERFIELDS_H
