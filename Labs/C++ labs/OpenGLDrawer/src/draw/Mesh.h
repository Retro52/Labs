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
#include "Texture.h"

class Mesh
{
private:
    unsigned int vao{}, vbo{};
    size_t vertices;
    glm::mat4 model;

    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;
    void Update();
public:

    glm::vec3 front, up, right, dir, position, scale, rotation;

    void Rotate(const glm::vec3 &deltaRotation);
    void Translate(const glm::vec3& deltaMove);
    void Scale(const glm::vec3& deltaScale);
    void RotateTo(glm::vec3& newRotation);
    void MoveTo(const glm::vec3& newLocation);
    void ScaleTo(const glm::vec3& newScale);
    Mesh(const float *buffer, size_t vertices, const int *attrs, std::shared_ptr<Shader> shader);
    Mesh(const float *buffer, size_t vertices, const int *attrs, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> &texture);
    Mesh(const float *buffer, size_t vertices, std::vector<int> attrs, std::shared_ptr<Shader> shader);
    Mesh(const float *buffer, size_t vertices, std::vector<int> attrs, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> &texture);
    ~Mesh();

    void draw(unsigned int primitive, const glm::mat4& project_view);
};


#endif //GRAPHICS_MESH_H
