//
// Created by Anton on 12.12.2021.
//

#include "Camera.h"
#include "../OpenGL/include/glm/ext.hpp"
#include "Window.h"

Camera::Camera(const glm::vec3& position, float fov) : position(position), fov(fov), zoom(1.0f), rotation(1.0f)
{
    Update();
}
/* TODO: Find math formulas for this */
void Camera::Update()
{
    front = glm::vec3(rotation * glm::vec4(0,0,-1,1));
    right = glm::vec3(rotation * glm::vec4(1,0,0,1));
    up = glm::vec3(rotation * glm::vec4(0,1,0,1));
    dir = glm::vec3(rotation * glm::vec4(0,0,-1,1));

    /* TODO: Consider understanding wtf is that and why we are setting y direction to 0
     * (except we always wanna this vector to be parallel to an horizon vector)*/
    dir.y = 0;

    float len = length(dir);

    if (len > 0.0f)
    {
        dir.x /= len;
        dir.z /= len;
    }
}
/*                   Roll      Pitch    Yaw    */
void Camera::rotate(float x, float y, float z)
{
    /* Yaw axis rotation */
    rotation = glm::rotate(rotation, z, glm::vec3(0,0,1));
    /* Pitch axis rotation */
    rotation = glm::rotate(rotation, y, glm::vec3(0,1,0));
    /* Roll axis rotation */
    rotation = glm::rotate(rotation, x, glm::vec3(1,0,0));

    Update();
}

glm::mat4 Camera::getProjection() const
{
    float aspect = (float) Window::getWidth() / (float) Window::getHeight();
    return glm::perspective(fov * zoom, aspect, 0.05f, 1500.0f);
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(position, position+front, up);
}