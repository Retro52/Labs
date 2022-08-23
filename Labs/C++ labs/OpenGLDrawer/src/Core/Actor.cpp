//
// Created by Anton on 14.08.2022.
//

#include "Actor.h"

/***
 * Rotate mesh on deltaRotation degrees (in radians)
 * @param deltaRotation three dimensional vector of rotation
 */
void Actor::Rotate(const glm::vec3 &deltaRotation)
{
    rotation += deltaRotation;
}

/**
 * Change mesh scale
 * @param deltaScale three dimensional vector of scale change at every axis
 */
void Actor::Scale(const glm::vec3& deltaScale)
{
    scale *= deltaScale;
}

/**
 * Change mesh position
 * @param deltaMove three dimensional vector of position change at every axis
 */
void Actor::Translate(const glm::vec3& deltaMove)
{
    position += deltaMove;
}

/**
 * Change mesh position
 * @param newLocation three dimensional vector of new position at every axis
 */
void Actor::MoveTo(const glm::vec3 &newLocation)
{
    position = newLocation;
}

/**
 * Change mesh scale
 * @param newScale three dimensional vector of new scale at every axis
 */
void Actor::ScaleTo(const glm::vec3 &newScale)
{
    scale = newScale;
}

/**
 * Change mesh rotation
 * @param newRotation three dimensional vector of new rotation at every axis (in radians)
 */
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

void Actor::Update() {}

void Actor::UpdateControls() {}
