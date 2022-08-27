//
// Created by Anton on 11.08.2022.
//

#ifndef GRAPHICS_DIRECTIONALLIGHT_H
#define GRAPHICS_DIRECTIONALLIGHT_H

#include "../include/OpenGL/include/glm/glm.hpp"

/* TODO: turn it into the singleton */
class DirectionalLight
{
public:
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    /**
     * Creates scene directional light (only one is supported)
     * @param dir directional strength
     * @param amb ambient strength
     * @param diff diffuse strength
     * @param spec specular strength
     */
    DirectionalLight(const glm::vec3& dir, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec);
    ~DirectionalLight() = default;

    void Display() const;
};


#endif //GRAPHICS_DIRECTIONALLIGHT_H
