//
// Created by Anton on 12.12.2021.
//

#include "Window.h"
#include "Global.h"
#include "../OpenGL/include/glm/ext.hpp"

/**
 * Creates new perspective camera
 * @param position camera world position
 * @param fov camera field of view, in degrees
 */
PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, float fov) : fov(fov), zoom(1.0f), posX(0.0), posY(0.0)
{
    this->position = position;
    model = glm::mat4(1.0f);
    front = glm::vec3(model * glm::vec4(0,0,-1,1));
    right = glm::vec3(model * glm::vec4(1,0,0,1));
    up    = glm::vec3(model * glm::vec4(0,1,0,1));
    dir   = glm::vec3(model * glm::vec4(0,0,-1,1));

    dir.y = 0;

    float len = glm::length(dir);

    if (len > 0.0f)
    {
        dir.x /= len;
        dir.z /= len;
    }
}

/**
 * Get projection matrix of camera
 * @return 4-dimensional projection matrix
 */
glm::mat4 PerspectiveCamera::getProjection()
{
    Update();
    float aspect = ((float) Window::getWidth()) / (float) Window::getHeight();
    return glm::perspective(fov * zoom, aspect, 0.05f, 1500.0f);
}

/**
 * Get view matrix of camera
 * @return 4-dimensional matrix of camera view
 */
glm::mat4 PerspectiveCamera::getView()
{
    Update();
    return glm::lookAt(position, position + front, up);
}


/**
 * Updates internal stuff
 */
void PerspectiveCamera::Update()
{
    model = glm::mat4(1.0f);
    /* Yaw axis rotation */
    model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));
    /* Pitch axis rotation */
    model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
//    /* Roll axis rotation */
    model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));

    front = glm::vec3(model * glm::vec4(0,0,-1,1));
    right = glm::vec3(model * glm::vec4(1,0,0,1));
    up = glm::vec3(model * glm::vec4(0,1,0,1));
    dir = glm::vec3(model * glm::vec4(0,0,-1,1));

    dir.y = 0;

    float len = glm::length(dir);

    if (len > 0.0f)
    {
        dir.x /= len;
        dir.z /= len;
    }
}

void PerspectiveCamera::UpdateControls()
{
    double delta = Global::GetWorldDeltaTime();
    int speed;

    /* PerspectiveCamera and meshes speed settings */
    if(EventsHandler::pressed(GLFW_KEY_LEFT_SHIFT))
    {
        speed = 10;
    }
    else if (EventsHandler::pressed(GLFW_KEY_LEFT_CONTROL))
    {
        speed = 1;
    }
    else
    {
        speed = 5;
    }

    /* PerspectiveCamera world position */
    if (EventsHandler::pressed(GLFW_KEY_W))
    {
        Translate(GetFront() * delta * speed);
    }
    if (EventsHandler::pressed(GLFW_KEY_S))
    {
        Translate(- GetFront() * delta * speed);
    }
    if (EventsHandler::pressed(GLFW_KEY_D))
    {
        Translate(GetRight() * delta * speed);
    }
    if (EventsHandler::pressed(GLFW_KEY_A))
    {
        Translate(- GetRight() * delta * speed);
    }

    float mouseSensitivity = 150.0f;
    /* PerspectiveCamera world orientation */
    if (EventsHandler::_cursor_locked)
    {
        posX += -EventsHandler::deltaX * delta * mouseSensitivity / (float) Window::getHeight() * 2;
        posY += -EventsHandler::deltaY  * delta * mouseSensitivity / (float) Window::getHeight() * 2;

        if (posY < - glm::radians(89.0f))
        {
            posY = - glm::radians(89.0f);
        }
        if (posY > glm::radians(89.0f))
        {
            posY = glm::radians(89.0f);
        }

        RotateTo(glm::vec3(posY, posX, 0.0f));

        Update();
    }
}
