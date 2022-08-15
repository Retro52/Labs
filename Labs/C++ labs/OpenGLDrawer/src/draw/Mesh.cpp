//
// Created by Anton on 12.12.2021.
//

#define GLEW_STATIC

#include <iostream>

#include "../logging/easylogging++.h"
#include "../OpenGL/include/GLEW/glew.h"
#include "../OpenGL/include/glm/glm.hpp"
#include "../OpenGL/include/glm/gtc/matrix_transform.hpp"
#include "../OpenGL/include/glm/gtx/transform.hpp"

#include "Mesh.h"
#include "../Core/Global.h"

/**
 * Constructor for Mesh class
 * @param buffer vertices buffer
 * @param vertices count of vertices
 * @param attrs list of attributes values, each value represents number of corresponding values at buffer array for every attribute
 * @param shader shader for displaying model
 * @param material texture for the mesh
 */
Mesh::Mesh(const float *buffer, size_t vertices, const int * attrs, std::shared_ptr<Shader> shader, std::shared_ptr<Material> &material) : vertices(vertices), shader(std::move(shader)), material(material)
{
    /* protected fields from parent class */
    scale = glm::vec3(1.0f);
    model = glm::mat4(1.0f);
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);

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
Mesh::Mesh(const float *buffer, size_t vertices, const int *attrs, std::shared_ptr<Shader> shader) : vertices(vertices), shader(std::move(shader))
{
    /* protected fields from parent class */
    scale = glm::vec3(1.0f);
    model = glm::mat4(1.0f);
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);

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
Mesh::Mesh(const float *buffer, size_t vertices, std::vector<int> attrs, std::shared_ptr<Shader> shader, std::shared_ptr<Material> &material) : Mesh(buffer, vertices, attrs.data(), std::move(shader), material){}

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
    if (material)
    {
        if (material->diffuse)
        {
            material->diffuse->bind();
        }
        else
        {
            LOG(WARNING) << "Mesh seems to be missing diffuse texture";
        }
    }
    else
    {
        LOG(WARNING) << "Mesh seems to be missing material";
    }
    glBindVertexArray(vao);
    glDrawArrays(primitive, 0, vertices);
    glBindVertexArray(0);
}

void Mesh::outline(unsigned int primitive, const glm::mat4 &project_view, const std::shared_ptr<Shader> &outline_shader)
{
    outline_shader->use();
    outline_shader->uniformMatrix("model", this->model);
    outline_shader->uniformMatrix("project_view", project_view);
    if (material)
    {
        material->diffuse->bind();
    }
    glBindVertexArray(vao);
    glDrawArrays(primitive, 0, vertices);
    glBindVertexArray(0);
}

void Mesh::Update()
{
    model = glm::translate(position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
}
