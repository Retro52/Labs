//
// Created by Anton on 14.08.2022.
//

#include "Actor.h"

Actor::Actor() : position(glm::vec3(0)), rotation(glm::vec3(0)), scale(glm::vec3(1))
{
    model = glm::mat4(1.0f);
    front = glm::vec3(model * glm::vec4(0,0,-1,1));
    right = glm::vec3(model * glm::vec4(1,0,0,1));
    up    = glm::vec3(model * glm::vec4(0,1,0,1));
    dir   = glm::vec3(model * glm::vec4(0,0,-1,1));
}

void Actor::Rotate(const glm::vec3 &deltaRotation)
{
    rotation += deltaRotation;
}

void Actor::Scale(const glm::vec3& deltaScale)
{
    scale *= deltaScale;
}

void Actor::Translate(const glm::vec3& deltaMove)
{
    position += deltaMove;
}

void Actor::MoveTo(const glm::vec3 &newLocation)
{
    position = newLocation;
}

void Actor::ScaleTo(const glm::vec3 &newScale)
{
    scale = newScale;
}

void Actor::RotateTo(const glm::vec3 &newRotation)
{
    rotation = newRotation;
}

glm::vec3 Actor::GetPosition()
{
    return position;
}

glm::vec3 Actor::GetRotation()
{
    return rotation;
}

glm::vec3 Actor::GetScale()
{
    return scale;
}

glm::vec3 Actor::GetFront()
{
    return front;
}

glm::vec3 Actor::GetRight()
{
    return right;
}

glm::vec3 Actor::GetDirection()
{
    return dir;
}
