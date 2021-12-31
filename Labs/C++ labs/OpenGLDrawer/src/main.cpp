#define GLEW_STATIC

/* Default libs */
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <future>

/* GL libs */
#include "OpenGL/include/GLEW/glew.h"
#include "OpenGL/include/GLFW/glfw3.h"
#include "OpenGL/include/glm/ext.hpp"

/* Custom classes */
#include "general/Camera.h"
#include "general/Window.h"
#include "general/EventsHandler.h"
#include "general/ThreadSafeQueue.h"

/* Functions for program */
#include "functions.h"

/* TODO: replace functions with custom class with static methods like Tick(), Events(), etc. */

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

    /* Loading shaders and textures for default model render */
    loadShaders();
    loadTextures();

    if (var::mainShader == nullptr || var::lightShader == nullptr)
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
    std::thread t1(loadMeshHair); std::thread t2(loadMeshFace); std::thread t3(loadMeshSphere); std::thread t4(createAxes);

    /* All the threads join main thread here */
    t1.join(); t2.join(); t3.join(); t4.join();

    /* Creating meshes*/
    setUp();

    /* Selecting first mash of array */
    var::selectedMesh = ThreadSafeQueue::getMeshes(ALL)[0];

    /* Camera world default values positions */
    float camX = 0.0f;
    float camY = 0.0f;

    /* World settings */
    auto lastTime = (float) glfwGetTime();
    float delta, speed, mouseSensitivity = 600.0F, rotationSpeed = 0.01f;
    long frame = 0;
    bool rotate = false;

    glfwSwapInterval(0);

    /* Rotation set up */
    glm::vec3 rotationAxisX(1, 0, 0), rotationAxisY(0, 0, 1), rotationAxisZ(0, 1, 0), currentRotationAxis(0, 1, 0), lightColor(1, 1, 1);
    int curAxis = OZ;
    int id = 0, min = 0, max;
    /* Hide mouse cursor */
    EventsHandler::toggleCursor();

    /* Creating thread to listen for user console commands */
    std::thread commandListener(listen); commandListener.detach();
    std::cout << "Program loaded" << std::endl;

    /* Tick event */
    while (!Window::isShouldClose())
    {
        /* Update selected mesh id */
        max = (int) ThreadSafeQueue::getMeshes(ALL).size() - 1;
        if (id > max)
        {
            id = max;
        }
        if (id < min)
        {
            id = min;
        }

        auto start = std::chrono::high_resolution_clock::now();

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
        /* Show/hide cursor */
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

        /* Move selected mesh */
        if (EventsHandler::pressed(GLFW_KEY_Y))
        {
            var::selectedMesh->Translate(glm::vec3(0, delta * speed, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_I))
        {
            var::selectedMesh->Translate(glm::vec3(0, -delta * speed, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_U))
        {
            var::selectedMesh->Translate(glm::vec3(0, 0, -delta * speed));
        }
        if (EventsHandler::pressed(GLFW_KEY_H))
        {
            var::selectedMesh->Translate(glm::vec3(-delta * speed, 0, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_K))
        {
            var::selectedMesh->Translate(glm::vec3(delta * speed, 0, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_J))
        {
            var::selectedMesh->Translate(glm::vec3(0, 0, delta * speed));
        }

        /* Speed up rotation */
        if (EventsHandler::pressed(GLFW_KEY_UP))
        {
            rotationSpeed *= 1.01F;
        }
        if (EventsHandler::pressed(GLFW_KEY_DOWN))
        {
            rotationSpeed *= .99F;
        }

        if(EventsHandler::justPressed(GLFW_KEY_DELETE))
        {
            ThreadSafeQueue::remove(var::selectedMesh);
        }

        /* Switch mesh */
        if (EventsHandler::justPressed(GLFW_KEY_RIGHT))
        {
            if (id == max)
            {
                id = min;
            }
            else
            {
                id++;
            }
            var::selectedMesh = ThreadSafeQueue::getMeshes(ALL)[id];
        }

        if (EventsHandler::justPressed(GLFW_KEY_LEFT))
        {
            if (id == min)
            {
                id = max;
            }
            else
            {
                id--;
            }
            var::selectedMesh = ThreadSafeQueue::getMeshes(ALL)[id];
        }

        /* Scale meshes */
        if (EventsHandler::pressed(GLFW_KEY_KP_ADD))
        {
            var::selectedMesh->Scale(glm::vec3(1.01, 1.01, 1.01));
        }
        if (EventsHandler::pressed(GLFW_KEY_KP_SUBTRACT))
        {
            var::selectedMesh->Scale(glm::vec3(.99, .99, .99));
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
            var::selectedMesh->Rotate(currentRotationAxis * delta * rotationSpeed);
        }

        var::selectedMesh = ThreadSafeQueue::getMeshes(ALL)[id];
        if (!var::tempArray.empty())
        {
            std::shared_ptr<Mesh> temp = std::make_shared<Mesh>(var::tempArray.data(), var::tempArray.size() / 8, attrs, var::defaultTexture);
            temp->Scale(glm::vec3(100, 100, 100));
            ThreadSafeQueue::push(temp, MESH);
            var::selectedMesh = temp;
            var::tempArray.clear();
        }

        /* Camera projection view */
        glm::mat4 proj_view = camera->getProjection() * camera->getView();

        /* World draw */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.05f,0.05f,0.1f,1);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        /* FIXME: this is stupid, we need some kind of storage for lights, so we can pull info about light from it, so we can apply shader variables into draw method call, not here */
        /* Apply lighting data to mainShader */
        var::mainShader->use();
        var::mainShader->uniform3f("proj_pos", camera->position.x, camera->position.y, camera->position.z);
        var::mainShader->uniform3f("light_pos",
                                   ThreadSafeQueue::getMeshes(LIGHT)[0]->position.x,
                                   ThreadSafeQueue::getMeshes(LIGHT)[0]->position.y,
                                   ThreadSafeQueue::getMeshes(LIGHT)[0]->position.z
                                   );
        var::mainShader->uniform3f("light_color", lightColor.r, lightColor.g, lightColor.b);
        drawMeshes(proj_view);


        /* Update light mesh color to match light color */
        var::lightShader->use();
        var::lightShader->uniform3f("v_color", lightColor.r, lightColor.g, lightColor.b);
        drawLights(proj_view);

        /* Draw axes at selected mesh location */
        var::axisShader->use();
        var::axisShader->uniform3f("v_color", lightColor.r, lightColor.g, lightColor.b);
        drawAxes(proj_view, var::selectedMesh->position, var::selectedMesh->scale);

        /* Outlining selected object */
        outlineMesh(proj_view);

        /* Swapping buffers and pulling user inputs */
        Window::swapBuffers();
        EventsHandler::pullEvents();
    }
    Window::terminate();
}