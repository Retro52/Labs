//
// Created by Anton on 12.12.2021.
//

#define GLEW_STATIC

#include <iostream>

#include "../OpenGL/include/GLEW/glew.h"
#include "../OpenGL/include/glm/glm.hpp"
#include "../OpenGL/include/glm/gtc/matrix_transform.hpp"

#include "Mesh.h"


Mesh::Mesh(const float *buffer, size_t vertices, const int * attrs, std::shared_ptr<Texture> &texture) : vertices(vertices), texture(texture)
{
    model = glm::mat4(1.0f);
    pos = glm::vec3(0.0f);

    /* vector with data length */
    int vertex_size = 0;
    for (int i = 0; attrs[i]; i++)
    {
        vertex_size += attrs[i];
    }


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);

    // attributes
    int offset = 0;
    for (int i = 0; attrs[i]; i++)
    {
        int size = attrs[i];
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += size;
    }

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Mesh::draw(unsigned int primitive, const std::unique_ptr<Shader> &shader, const glm::mat4& project_view) const
{
    shader->use();
    shader->uniformMatrix("model", model);
    shader->uniformMatrix("project_view", project_view);
    if (texture)
    {
        texture->bind();
    }
    glBindVertexArray(vao);
    glDrawArrays(primitive, 0, vertices);
    glBindVertexArray(0);
}

void Mesh::rotate(const glm::vec3& axisRotation, float angle)
{
    model = glm::rotate(model, angle, axisRotation);
}

void Mesh::scale(const glm::vec3& deltaScale)
{
    model = glm::scale(model, deltaScale);
}

void Mesh::translate(const glm::vec3& deltaMove)
{
    pos += deltaMove;
    model = glm::translate(model, deltaMove);
}

Mesh::Mesh(const float *buffer, size_t vertices, const int *attrs) : vertices(vertices)
{
    model = glm::mat4(1.0f);
    pos = glm::vec3(0.0f);

    /* vector with data length */
    int vertex_size = 0;
    for (int i = 0; attrs[i]; i++)
    {
        vertex_size += attrs[i];
    }


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);

    // attributes
    int offset = 0;
    for (int i = 0; attrs[i]; i++)
    {
        int size = attrs[i];
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += size;
    }

    glBindVertexArray(0);
}
