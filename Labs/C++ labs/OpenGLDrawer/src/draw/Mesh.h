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
#include "Shader.h"
#include "Material.h"
#include "../Core/Actor.h"

class Mesh : public Actor
{
private:
    unsigned int vao{}, vbo{};
    size_t vertices;

    std::shared_ptr<Shader> shader;
    std::shared_ptr<Material> material;
    void Update() override;
public:

    Mesh(const float *buffer, size_t vertices, const int *attrs, std::shared_ptr<Shader> shader);
    Mesh(const float *buffer, size_t vertices, std::vector<int> attrs, std::shared_ptr<Shader> shader);
    Mesh(const float *buffer, size_t vertices, const int *attrs, std::shared_ptr<Shader> shader, std::shared_ptr<Material> &material);
    Mesh(const float *buffer, size_t vertices, std::vector<int> attrs, std::shared_ptr<Shader> shader, std::shared_ptr<Material> &material);
    ~Mesh();

    void draw(unsigned int primitive, const glm::mat4 &project_view);
    void outline(unsigned int primitive, const glm::mat4 &project_view, const std::shared_ptr<Shader> &outline_shader);
};


#endif //GRAPHICS_MESH_H
