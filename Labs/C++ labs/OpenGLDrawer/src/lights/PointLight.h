//
// Created by Anton on 11.08.2022.
//

#ifndef GRAPHICS_POINTLIGHT_H
#define GRAPHICS_POINTLIGHT_H

#include "../OpenGL/include/glm/glm.hpp"

class PointLight
{
public:
    glm::vec3 position;

    float affectDistance { 500.0f };

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    PointLight(const glm::vec3 &pos, const glm::vec3 &amb, const glm::vec3 &diff, const glm::vec3 &spec, float con, float lin, float quad);
    ~PointLight() = default;

    void Display() const;
};


#endif //GRAPHICS_POINTLIGHT_H
