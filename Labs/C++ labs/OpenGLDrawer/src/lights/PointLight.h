//
// Created by Anton on 11.08.2022.
//

#ifndef GRAPHICS_POINTLIGHT_H
#define GRAPHICS_POINTLIGHT_H

#include "../OpenGL/include/glm/glm.hpp"
#include "../draw/Mesh.h"
#include "Light.h"

class PointLight : Light
{
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    PointLight(const glm::vec3& pos, float con, float lin, float quad, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec);
    PointLight(const glm::vec3& pos, float con, float lin, float quad, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const std::shared_ptr<Mesh>& m);
    ~PointLight() = default;
};


#endif //GRAPHICS_POINTLIGHT_H
