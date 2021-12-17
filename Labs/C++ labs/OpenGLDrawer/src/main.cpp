#define GLEW_STATIC

/* Default libs */
#include <iostream>
#include <memory>
#include <thread>

/* GL libs */
#include "OpenGL/include/GLEW/glew.h"
#include "OpenGL/include/GLFW/glfw3.h"
#include "OpenGL/include/glm/ext.hpp"

/* Custom classes */
#include "general/Camera.h"
#include "general/Window.h"
#include "general/EventsHandler.h"
#include "draw/Mesh.h"
#include "loaders/objLoader.h"

/* Attributes array */
int attrs[] =
{
        /* Creates to support texture attributes to load into shader */
        /* 3: defines position - x, y, z */
        /* 2: stands for u, v - texture coordinates*/
        /* 3: stands for normal vector*/
        /* 0 is for terminating "for" loop (stupid, but works) */
        3,2,3,0
};

/* Axis enum class */
enum AXIS
{
    OX = 0,
    OY = 1,
    OZ = 2
};

/* Namespace for global variables into main.cpp file */
namespace var
{
    /* Shaders */
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> ligts;

    /* Textures */
    std::shared_ptr<Texture> faceTexture;
    std::shared_ptr<Texture> hairTexture;

    /* Meshes vertex arrays */
    std::vector<float> faceArray;
    std::vector<float> hairArray;
    std::vector<float> cubeArray;
}

/***
 * Function for loading all the shaders
***/
void loadShaders()
{
    /* Load shader for drawing */
    std::cout << "Compiling shaders" << std::endl;
    load_shader("../res/mainv.glsl", "../res/mainf.glsl", var::shader);
    load_shader("../res/lightv.glsl", "../res/lightf.glsl", var::ligts);
    std::cout << "Shaders compiled" << std::endl;
}
/***
 * Function for loading all the textures
***/
void loadTextures()
{
    std::cout << "Loading textures" << std::endl;
    load_texture("../res/Claire/Face/face.png", var::faceTexture);
    load_texture("../res/Claire/Hair/hair.png", var::hairTexture);
    std::cout << "Textures loaded" << std::endl;
}

/***
 * Function for loading hair mesh
***/
void loadMeshHair()
{
    std::cout << "Loading Hair mesh" << std::endl;
    objLoader::loadObjModel("../res/Claire/Hair/hairTotal.obj", var::hairArray);
    std::cout << "Hair mesh loaded" << std::endl;
}

/***
 * Function for loading face mesh
***/
void loadMeshFace()
{
    std::cout << "Loading Face mesh" << std::endl;
    objLoader::loadObjModel("../res/Claire/Face/faceTotal.obj", var::faceArray);
    std::cout << "Face mesh loaded" << std::endl;
}

/***
 * Function for loading sphere mesh
***/
void loadMeshSphere()
{
    std::cout << "Loading Sphere mesh" << std::endl;
    objLoader::loadObjModel("../res/Basics/sphere.obj", var::cubeArray);
    std::cout << "Sphere mesh loaded" << std::endl;
}


int main(int argc, char ** argv)
{
    /* Program initialization */
    Window::init(1920, 1080, "Lab 4");
    std::cout << "Window initialized" << std::endl;
    EventsHandler::init();
    std::cout << "Events handler initialized" << std::endl;

    /* Creating main camera */
    std::unique_ptr<Camera> camera = std::make_unique<Camera>(glm::vec3(0,0,1), glm::radians(90.0f));
    std::cout << "Camera created" << std::endl;

    /* TODO: remake project to use smart pointers only, add multiple lights support */
    loadShaders();
    loadTextures();

    if (var::shader == nullptr || var::ligts == nullptr)
    {
        std::cerr << "[ERROR]::MAIN Failed to load shaders" << std::endl;
        Window::terminate();
        return 1;
    }
    if (var::faceTexture == nullptr || var::hairTexture == nullptr)
    {
        std::cerr << "[ERROR]::MAIN Failed to load textures" << std::endl;
        Window::terminate();
        return 1;
    }

    /***
     * Loading models vertex arrays in multithreading for better performance
     * Interesting comparison:
     * without multithreading it takes 6.4 seconds to launch the program, with multithreading - 3.1
     * ***/
    std::thread t1(loadMeshHair); std::thread t2(loadMeshFace); std::thread t3(loadMeshSphere);

    /* All the threads join main thread here */
    t1.join(); t2.join(); t3.join();

    /* Creating meshes*/
    std::unique_ptr<Mesh> faceMesh = std::make_unique<Mesh>(var::faceArray.data(), var::faceArray.size() / 8, attrs, var::faceTexture);
    std::unique_ptr<Mesh> hairMesh = std::make_unique<Mesh>(var::hairArray.data(), var::hairArray.size() / 8, attrs, var::hairTexture);
    std::unique_ptr<Mesh> lightMesh = std::make_unique<Mesh>(var::cubeArray.data(), var::cubeArray.size() / 8, attrs);

    /* Camera world default values positions */
    float camX = 0.0f;
    float camY = 0.0f;

    /* World settings */
    auto lastTime = (float) glfwGetTime();
    float delta, speed, mouseSensitivity = 1200.0F, rotationSpeed = 0.01f;
    long frame = 0;
    bool rotate = false;

    std::cout << var::faceArray.size() << std::endl;
    glfwSwapInterval(0);

    /* Hide mouse cursor */
    EventsHandler::toggleCursor();

    /* Setting meshes default positions */     /*       x           z           y      */
    lightMesh->translate(glm::vec3(-23.1508, 115.151, 146.096));
    faceMesh->scale(glm::vec3(100, 100, 100));
    hairMesh->scale(glm::vec3(100, 100, 100));


    glm::vec3 rotationAxisX(1, 0, 0), rotationAxisY(0, 0, 1),
    rotationAxisZ(0, 1, 0), currentRotationAxis(0, 1, 0), lightColor(1, 1, 1);
    int curAxis = OZ;
    std::cout << "Program loaded" << std::endl;

    /* Tick event */
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

        /* Camera and meshes speed settings */
        if(EventsHandler::pressed(GLFW_KEY_LEFT_SHIFT))
        {
            speed = 200;
        }
        else if (EventsHandler::pressed(GLFW_KEY_LEFT_CONTROL))
        {
            speed = 1;
        }
        else
        {
            speed = 5;
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
        if (EventsHandler::pressed(GLFW_KEY_Y))
        {
            lightMesh->translate(glm::vec3(0, delta * speed, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_I))
        {
            lightMesh->translate(glm::vec3(0, -delta * speed, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_J))
        {
            lightMesh->translate(glm::vec3(0, 0, - delta * speed));
        }
        if (EventsHandler::pressed(GLFW_KEY_H))
        {
            lightMesh->translate(glm::vec3(-delta * speed, 0, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_K))
        {
            lightMesh->translate(glm::vec3(delta * speed, 0, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_U))
        {
            lightMesh->translate(glm::vec3(0, 0, delta * speed));
        }
        if (EventsHandler::pressed(GLFW_KEY_UP))
        {
            rotationSpeed *= 1.01F;
        }
        if (EventsHandler::pressed(GLFW_KEY_DOWN))
        {
            rotationSpeed *= .99F;
        }
        if (EventsHandler::pressed(GLFW_KEY_KP_ADD))
        {
            faceMesh->scale(glm::vec3(1.01, 1.01, 1.01));
            hairMesh->scale(glm::vec3(1.01, 1.01, 1.01));
        }
        if (EventsHandler::pressed(GLFW_KEY_KP_SUBTRACT))
        {
            faceMesh->scale(glm::vec3(.99, .99, .99));
            hairMesh->scale(glm::vec3(.99, .99, .99));
        }
        if (EventsHandler::justPressed(GLFW_KEY_SPACE))
        {
            switch (curAxis)
            {
                case OX:
                    currentRotationAxis = rotationAxisY;
                    curAxis = OY;
                    break;
                case OY:
                    currentRotationAxis = rotationAxisZ;
                    curAxis = OZ;
                    break;
                case OZ:
                    currentRotationAxis = rotationAxisX;
                    curAxis = OX;
                    break;
                default:
                    break;
            }
        }

        /* Model rotation */
        if (EventsHandler::justClicked(GLFW_MOUSE_BUTTON_2))
        {
            rotate = !rotate;
        }
        if (rotate)
        {
            faceMesh->rotate(currentRotationAxis, delta * rotationSpeed);
            hairMesh->rotate(currentRotationAxis, delta * rotationSpeed);
        }

        /* Change color */
        if (EventsHandler::clicked(GLFW_MOUSE_BUTTON_1))
        {
            if(lightColor.z > 0.1F)
            {
                lightColor.z -= delta;
            }
            else
            {
                lightColor.z = 1.0F;
            }
        }

        /* Camera projection view */
        glm::mat4 proj_view = camera->getProjection() * camera->getView();

        /* World draw */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.05f,0.05f,0.1f,1);

        /* Apply lighting data to shader */
        var::shader->use();
        var::shader->uniform3f("proj_pos", camera->position.x, camera->position.y, camera->position.z);
        var::shader->uniform3f("light_pos", lightMesh->pos.x, lightMesh->pos.y, lightMesh->pos.z);
        var::shader->uniform3f("light_color", lightColor.r, lightColor.g, lightColor.b);

        /* Debug faceMesh draw*/
        faceMesh->draw(GL_TRIANGLES, var::shader, proj_view);
        hairMesh->draw(GL_TRIANGLES, var::shader, proj_view);

        /* Update light mesh color to match light color */
        var::ligts->use();
        var::ligts->uniform3f("v_color", lightColor.r, lightColor.g, lightColor.b);
        lightMesh->draw(GL_TRIANGLES, var::ligts, proj_view);
        Window::swapBuffers();
        EventsHandler::pullEvents();
    }
    Window::terminate();
}