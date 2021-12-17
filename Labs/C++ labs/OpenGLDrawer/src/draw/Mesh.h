//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

#include <cstdlib>
#include <vector>
#include <memory>
#include <freeglut.h>
#include "../OpenGL/include/glm/glm.hpp"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"

class Mesh
{
    unsigned int vao{}, vbo{};
    size_t vertices;
    glm::mat4 model;
    std::shared_ptr<Texture> texture;
public:
    glm::vec3 pos;
    void rotate(const glm::vec3& axisRotation, float angle);
    void scale(const glm::vec3& deltaScale);
    void translate(const glm::vec3& deltaMove);
    Mesh(const float *buffer, size_t vertices, const int *attrs);
    Mesh(const float *buffer, size_t vertices, const int *attrs, std::shared_ptr<Texture> &texture);
    ~Mesh();

    void draw(unsigned int primitive, const std::unique_ptr<Shader> &shader, const glm::mat4& project_view) const;
};


#endif //GRAPHICS_MESH_H
