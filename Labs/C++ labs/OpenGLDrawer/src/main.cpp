#define GLEW_STATIC

/* Default libs */
#include <iostream>
#include <memory>
#include <string>

/* GL libs */
#include "OpenGL/include/GLEW/glew.h"
#include "OpenGL/include/GLFW/glfw3.h"
#include "OpenGL/include/glm/ext.hpp"

/* Custom classes */
#include "general/Camera.h"
#include "general/Window.h"
#include "general/EventsHandler.h"
//#include "loaders/objLoader.h"
#include "draw/Mesh.h"
#include "draw/Shader.h"
#include "draw/Texture.h"
#include "loaders/objModel.h"

float vertices[] = {
        // x    y     z     u     v
        -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int attrs[] = {
        3,2,0 //null terminator
};

GLuint VAO, VBO;

void debug()
{
    // Create VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

int main(int argc, char** argv)
{
    /* Program initialization */
    Window::init(1920, 1080, "Lab 4");
    EventsHandler::init();

    /* Creating main camera */
    std::unique_ptr<Camera> camera = std::make_unique<Camera>(glm::vec3(0,0,1), glm::radians(90.0f));

    /* Load shader for drawing (recommended, but actually not required, you CAN display things without shader, but you better not to) */
    /*TODO: use smart pointer instead of dangerous C-styled one, check for errors*/
    Shader * shader = load_shader("../res/mainv.glsl", "../res/mainf.glsl");
    if (shader == nullptr)
    {
        std::cerr << "failed to load shader" << std::endl;
        Window::terminate();
        return 1;
    }

    /* TODO: use smart pointers & check for errors */

    Texture * texture = load_texture("../res/img.png");
    if (texture == nullptr)
    {
        Window::terminate();
        return 2;
    }

    /* Loading default mesh */

    auto * objmodel = new objModel();
    std::vector<float> test = objmodel->loadObjModel("example.obj");
    std::vector<float> test2 = objmodel->loadObjModel("../res/cylinder.obj");
    std::vector<float> test3 = objmodel->loadObjModel("../res/doubleCube.obj");
    if (test3.empty())
    {
        std::cerr << "test2 is empty!" << std::endl;
        exit(1);
    }
    std::cout << test.size() << std::endl;
    /* Camera world default values positions */
    float camX = 0.0f;
    float camY = 0.0f;

    /* World delta time settings */
    auto lastTime = (float ) glfwGetTime();
    float delta, speed = 4.0F, mouseSensitivity = 1200.0F;

    long frame = 0;
    glfwSwapInterval(0);


    glClearColor(0.6f,0.62f,0.65f,1);

    EventsHandler::toggleCursor();

    glm::mat4 model(1.0f);

    Mesh * mesh = new Mesh(test.data(), test.size() / 5, attrs);
    Mesh * mesh2 = new Mesh(vertices, 6, attrs);
    Mesh * mesh3 = new Mesh(test2.data(), test2.size() / 5, attrs);
    Mesh * mesh4 = new Mesh(test3.data(), test3.size() / 5, attrs);
    while (!Window::isShouldClose())
    {
        /* Global tick events */
        frame++;
        auto currentTime = (float) glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        /* Check if have to close window */
        if (EventsHandler::justPressed(GLFW_KEY_ESCAPE))
        {
            Window::setShouldClose(true);
        }

        if (EventsHandler::justPressed(GLFW_KEY_TAB))
        {
            EventsHandler::toggleCursor();
        }

        /* Camera world orientation */
        if (EventsHandler::_cursor_locked)
        {
            camY += -EventsHandler::deltaY  * delta * mouseSensitivity / (float) Window::getHeight() * 2;
            camX += -EventsHandler::deltaX * delta * mouseSensitivity / (float) Window::getHeight() * 2;

            if (camY < - glm::radians(89.0f))
            {
                camY = - glm::radians(89.0f);
            }
            if (camY > glm::radians(89.0f))
            {
                camY = glm::radians(89.0f);
            }

            camera->rotation = glm::mat4(1.0f);
            camera->rotate(camY, camX, 0);
        }

        /* Camera world position */
        if (EventsHandler::pressed(GLFW_KEY_W))
        {
            camera->position += camera->front * delta * speed;
        }
        if (EventsHandler::pressed(GLFW_KEY_S))
        {
            camera->position -= camera->front * delta * speed;
        }
        if (EventsHandler::pressed(GLFW_KEY_D))
        {
            camera->position += camera->right * delta * speed;
        }
        if (EventsHandler::pressed(GLFW_KEY_A))
        {
            camera->position -= camera->right * delta * speed;
        }


        /* Shaders and texture */
        shader->use();
        shader->uniformMatrix("model", model);
        shader->uniformMatrix("project_view", camera->getProjection()*camera->getView());
        texture->bind();

        /* World draw */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.8f,0.4f,0.2f,1);

        /* Updating matrix */
        model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        /* debug mesh draw*/
        mesh->draw(GL_TRIANGLES);
//        mesh2->draw(GL_TRIANGLES);
//        mesh3->draw(GL_TRIANGLE_FAN);
//        mesh4->draw(GL_TRIANGLE_STRIP);
        Window::swapBuffers();
        EventsHandler::pullEvents();
    }
}