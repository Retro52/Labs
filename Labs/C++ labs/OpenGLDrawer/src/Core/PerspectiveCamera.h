//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_PERSPECTIVECAMERA_H
#define GRAPHICS_PERSPECTIVECAMERA_H

#include "../OpenGL/include/glm/glm.hpp"
#include "Actor.h"
#include <iostream>

class PerspectiveCamera : public Actor
{
public:
    float fov, zoom;
    double posX, posY;
    PerspectiveCamera(const glm::vec3& position, float fov);


    void Update() override;
    void UpdateControls() override;
    void Draw(const Shader& shader) override {};

    glm::mat4 getProjection();
    glm::mat4 getView();
};

#endif //GRAPHICS_PERSPECTIVECAMERA_H
