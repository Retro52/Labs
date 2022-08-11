#define GLEW_STATIC

/* TODO: create a namespace for the project*/

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
#include "general/PerspectiveCamera.h"
#include "general/Window.h"
#include "general/EventsHandler.h"
#include "general/ThreadSafeQueue.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"

/* Functions for program */
#include "functions.h"

/* TODO: replace functions with custom class with static methods like Tick(), Events(), etc. */
/* TODO: add comments doxygen-style */

/**
 * Program entry point
 * @param argc command-line arguments count
 * @param argv command-line arguments
 * @return exit code
 */
int main(int argc, char ** argv)
{
    /* Program initialization */
    Window::init(1920, 1080, "Lab 4");
    std::cout << "Window initialized" << std::endl;
    EventsHandler::init();
    std::cout << "Events handler initialized" << std::endl;

    /* Creating main camera */
    std::unique_ptr<PerspectiveCamera> camera = std::make_unique<PerspectiveCamera>(glm::vec3(0, 0, 150), glm::radians(90.0f));
    std::cout << "Perspective Camera created" << std::endl;

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
    std::thread t2(loadMeshFace); std::thread t3(loadMeshSphere); std::thread t4(createAxes);

    /* All the threads join main thread here */
    t2.join(); t3.join(); t4.join();

    /* Creating meshes*/
    setUp();

    /* Selecting first mash of array */
    var::selectedMesh = ThreadSafeQueue::getMeshes(ALL)[0];

    /* PerspectiveCamera world default values positions */
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

    std::shared_ptr<DirectionalLight> dirLight = std::make_shared<DirectionalLight>(
            glm::vec3(-0.2f, -1.0f, -0.3f),
            glm::vec3(0.05f, 0.05f, 0.05f),
            glm::vec3(0.4f, 0.4f, 0.4f),
            glm::vec3(0.5f, 0.5f, 0.5f));


    /* Tick event */
    while (!Window::isShouldClose())
    {
        system("cls");
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
        std::cout << "Delta : " << delta << "\n";
        std::cout << "FPS : " << 1000.0f / delta << "\n";

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

        /* PerspectiveCamera world orientation */
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

        /* PerspectiveCamera and meshes speed settings */
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

        /* PerspectiveCamera world position */
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

        /* replace with % instead of this */
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
        /** @deprecated */
        if (!var::tempArray.empty())
        {
            std::shared_ptr<Mesh> temp = std::make_shared<Mesh>(var::tempArray.data(), var::tempArray.size() / 8, attributes, var::mainShader, var::defaultTexture);
            temp->Scale(glm::vec3(100, 100, 100));
            ThreadSafeQueue::push(temp, MESH);
            var::selectedMesh = temp;
            var::tempArray.clear();
        }

        /* PerspectiveCamera projection view */
        glm::mat4 proj_view = camera->getProjection() * camera->getView();

        /* TODO: change this */
        /* World background draw */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.05f,0.05f,0.1f,1);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        /* FIXME: this is stupid, we need some kind of storage for lights, so we can pull info about light from it, so we can apply shader variables into draw method call, not here */
        /* TODO: improve either shader or render for ~infinite point light support (current limit is 16)*/

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
        /* TODO: put it to the separate method of the new static class, Scene or Root, for ex. */
//        var::mainShader->uniform1i("material.diffuse", 0);
//        var::mainShader->uniform1i("material.specular", 1);
        /* 32.0f - magic shininess value taken from OpenGL tutorial, needs replacement */
//        var::mainShader->uniform1f("material.shininess", 32.0f);

        /** @test directional light to shader transfer */
        var::mainShader->uniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
//        var::mainShader->uniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        var::mainShader->uniform3f("dirLight.ambient", 0.15f, 0.15f, 0.15f);
        var::mainShader->uniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        var::mainShader->uniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);

        var::mainShader->uniform1i("NR_POINT_LIGHTS", 1);

        /** @test point light transfer to shader */
//        var::mainShader->uniform3f("pointLights[0].position", 0.0f, 0.0f, 0.0f);
        auto temp = ThreadSafeQueue::getMeshes(LIGHT)[0]->position;

        std::cout << temp.x << " : " << temp.y << " : " << temp.z << "\n";
        var::mainShader->uniform3f("pointLights[0].position", temp.x, temp.y, temp.z);
        var::mainShader->uniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        var::mainShader->uniform3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        var::mainShader->uniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        var::mainShader->uniform1f("pointLights[0].constant", 1.0f);
        var::mainShader->uniform1f("pointLights[0].linear", 0.09f);
        var::mainShader->uniform1f("pointLights[0].quadratic", 0.032f);

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