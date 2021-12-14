//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

#include <cstdlib>
#include <vector>
#include <freeglut.h>
#include "../OpenGL/include/glm/glm.hpp"
#include "Vertex.h"

class Mesh
{
    unsigned int vao;
    unsigned int vbo;
    size_t vertices;
public:
    Mesh(const float* buffer, size_t vertices, const int* attrs);
    Mesh(const std::vector<float>& buffer, size_t vertices, const int* attrs);
    ~Mesh();

    void draw(unsigned int primitive) const;
};


#endif //GRAPHICS_MESH_H
