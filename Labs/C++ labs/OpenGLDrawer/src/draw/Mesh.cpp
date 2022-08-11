//
// Created by Anton on 12.12.2021.
//

#define GLEW_STATIC

#include <iostream>
#include <utility>

#include "../OpenGL/include/GLEW/glew.h"
#include "../OpenGL/include/glm/glm.hpp"
#include "../OpenGL/include/glm/gtc/matrix_transform.hpp"
#include "../OpenGL/include/glm/gtx/transform.hpp"

#include "Mesh.h"

/**
 * Constructor for Mesh class
 * @param buffer vertices buffer
 * @param vertices count of vertices
 * @param attrs list of attributes values, each value represents number of corresponding values at buffer array for every attribute
 * @param shader shader for displaying model
 * @param texture texture for the mesh
 */
Mesh::Mesh(const float *buffer, size_t vertices, const int * attrs, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> &texture) : vertices(vertices), shader(std::move(shader)), rotation(0.0f), position(0.0f), model(1.0f), scale(1.0f), texture(texture)
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

/**
 * Constructor for Mesh class
 * @param buffer vertices buffer
 * @param vertices count of vertices
 * @param attrs list of attributes values, each value represents number of corresponding values at buffer array for every attribute
 * @param shader shader for displaying model
 */
Mesh::Mesh(const float *buffer, size_t vertices, const int *attrs, std::shared_ptr<Shader> shader) : vertices(vertices), shader(std::move(shader)), rotation(0.0f), position(0.0f), model(1.0f), scale(1.0f)
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

/**
 * Constructor for Mesh class
 * @param buffer vertices buffer
 * @param vertices count of vertices
 * @param attrs list of attributes values, each value represents number of corresponding values at buffer array for every attribute
 * @param shader shader for displaying model
 * @param texture texture for the mesh
 */
Mesh::Mesh(const float *buffer, size_t vertices, std::vector<int> attrs, std::shared_ptr<Shader> shader) : Mesh(buffer, vertices, attrs.data(), std::move(shader)){}

/**
 * Constructor for Mesh class
 * @param buffer vertices buffer
 * @param vertices count of vertices
 * @param attrs list of attributes values, each value represents number of corresponding values at buffer array for every attribute
 * @param shader shader for displaying model
 */
Mesh::Mesh(const float *buffer, size_t vertices, std::vector<int> attrs, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> &texture) : Mesh(buffer, vertices, attrs.data(), shader, texture){}

/**
 * Mesh class destructor, deletes mesh from gl memory
 */
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

/**
 * Draws this mesh
 * @param primitive drawing mode, better use GL_TRIANGLES by default
 * @param project_view project view matrix, extracted from camera
 */
void Mesh::draw(unsigned int primitive, const glm::mat4& project_view)
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

/***
 * Rotate mesh on deltaRotation degrees (in radians)
 * @param deltaRotation three dimensional vector of rotation
 */
void Mesh::Rotate(const glm::vec3 &deltaRotation)
{
    rotation += deltaRotation;
}

/**
 * Change mesh scale
 * @param deltaScale three dimensional vector of scale change at every axis
 */
void Mesh::Scale(const glm::vec3& deltaScale)
{
    scale *= deltaScale;
}

/**
 * Change mesh position
 * @param deltaMove three dimensional vector of position change at every axis
 */
void Mesh::Translate(const glm::vec3& deltaMove)
{
    position += deltaMove;
}

/**
 * Change mesh position
 * @param newLocation three dimensional vector of new position at every axis
 */
void Mesh::MoveTo(const glm::vec3 &newLocation)
{
    position = newLocation;
}

/**
 * Change mesh scale
 * @param newScale three dimensional vector of new scale at every axis
 */
void Mesh::ScaleTo(const glm::vec3 &newScale)
{
    scale = newScale;
}

/**
 * Change mesh rotation
 * @param newRotation three dimensional vector of new rotation at every axis (in radians)
 */
void Mesh::RotateTo(glm::vec3 &newRotation)
{
    rotation = newRotation;
}

/**
 * Updates all internal matrices necessary after any scale, position or rotation update
 */
void Mesh::Update()
{
    model = glm::translate(position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
}
