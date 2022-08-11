//
// Created by Anton on 12.12.2021.
//

#include "PerspectiveCamera.h"
#include "../OpenGL/include/glm/ext.hpp"
#include "Window.h"

/**
 * Creates new perspective camera
 * @param position camera world position
 * @param fov camera field of view, in degrees
 */
PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, float fov) : position(position), fov(fov), zoom(1.0f), rotation(1.0f)
{
    Update();
}

void PerspectiveCamera::Update()
{
    front = glm::vec3(rotation * glm::vec4(0,0,-1,1));
    right = glm::vec3(rotation * glm::vec4(1,0,0,1));
    up = glm::vec3(rotation * glm::vec4(0,1,0,1));
    dir = glm::vec3(rotation * glm::vec4(0,0,-1,1));

    dir.y = 0;

    float len = glm::length(dir);

    if (len > 0.0f)
    {
        dir.x /= len;
        dir.z /= len;
    }
}

/**
 * Rotate camera on x, y, z angles at every dimension, angles in radians
 * @param x rotation angle for X axis, in radians
 * @param y rotation angle for Y axis, in radians
 * @param z rotation angle for Z axis, in radians
 */
void PerspectiveCamera::rotate(float x, float y, float z)
{
    /* Yaw axis rotation */
    rotation = glm::rotate(rotation, z, glm::vec3(0,0,1));
    /* Pitch axis rotation */
    rotation = glm::rotate(rotation, y, glm::vec3(0,1,0));
    /* Roll axis rotation */
    rotation = glm::rotate(rotation, x, glm::vec3(1,0,0));

    Update();
}

/**
 * Get projection matrix of camera
 * @return 4-dimensional projection matrix
 */
glm::mat4 PerspectiveCamera::getProjection() const
{
    float aspect = (float) Window::getWidth() / (float) Window::getHeight();
    return glm::perspective(fov * zoom, aspect, 0.05f, 1500.0f);
}

/**
 * Get view matrix of camera
 * @return 4-dimensional matrix of camera view
 */
glm::mat4 PerspectiveCamera::getView() const
{
    return glm::lookAt(position, position+front, up);
}