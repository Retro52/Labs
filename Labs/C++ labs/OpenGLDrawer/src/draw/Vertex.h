//
// Created by Anton on 14.12.2021.
//

#ifndef GRAPHICS_VERTEX_H
#define GRAPHICS_VERTEX_H

#include "../OpenGL/include/glm/glm.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texcoord;
};

#endif //GRAPHICS_VERTEX_H
