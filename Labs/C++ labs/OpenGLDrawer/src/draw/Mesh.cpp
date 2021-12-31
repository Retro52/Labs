//
// Created by Anton on 12.12.2021.
//

#define GLEW_STATIC

#include <iostream>

#include "../OpenGL/include/GLEW/glew.h"
#include "../OpenGL/include/glm/glm.hpp"
#include "../OpenGL/include/glm/gtc/matrix_transform.hpp"
#include "../OpenGL/include/glm/gtx/transform.hpp"

#include "Mesh.h"


Mesh::Mesh(const float *buffer, size_t vertices, const int * attrs, std::shared_ptr<Texture> &texture) : vertices(vertices), rotation(0.0f), position(0.0f), model(1.0f), scale(1.0f), texture(texture)
{
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

void Mesh::draw(unsigned int primitive, const std::unique_ptr<Shader> &shader, const glm::mat4& project_view)
{
    Update();
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

void Mesh::Rotate(const glm::vec3 &deltaRotation)
{
    rotation += deltaRotation;
}

void Mesh::Scale(const glm::vec3& deltaScale)
{
    scale *= deltaScale;
}

void Mesh::Translate(const glm::vec3& deltaMove)
{
    position += deltaMove;
}


void Mesh::MoveTo(const glm::vec3 &newLocation)
{
    position = newLocation;
}


void Mesh::ScaleTo(const glm::vec3 &newScale)
{
    scale = newScale;
}

Mesh::Mesh(const float *buffer, size_t vertices, const int *attrs) : vertices(vertices), rotation(0.0f), position(0.0f), model(1.0f), scale(1.0f)
{

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

/* Reset matrices */
void Mesh::Update()
{
    model = glm::translate(position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
}


