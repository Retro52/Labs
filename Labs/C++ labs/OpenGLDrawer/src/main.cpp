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
#include "loaders/objLoader.h"

/*TODO: replace with vector; move to variables namespace*/
/* Attributes array */
int attrs[] =
{
        /* Creates to support texture attributes to load into mainShader */
        /* 3: defines position - x, y, z */
        /* 2: stands for u, v - texture coordinates*/
        /* 3: stands for normal vector*/
        /* 0 is for terminating "for" loop (stupid, but works) */
        3,2,3,0
};

/* Axis enum class */
enum AXIS
{
    OX, OY, OZ
};

/* Namespace for global variables into main.cpp file */
namespace var
{
    /* Shaders */
    std::unique_ptr<Shader> mainShader;
    std::unique_ptr<Shader> lightShader;
    std::unique_ptr<Shader> axisShader;
    std::unique_ptr<Shader> outlineShader;

    /* Textures */
    std::shared_ptr<Texture> faceTexture;
    std::shared_ptr<Texture> hairTexture;
    std::shared_ptr<Texture> defaultTexture;

    /* Meshes vertex arrays */
    std::vector<float> faceArray;
    std::vector<float> hairArray;
    std::vector<float> cubeArray;
    std::vector<float> tempArray;
    std::vector<float> oxArr, oyArr, ozArr;

    std::shared_ptr<Mesh> selectedMesh;
}

/***
 * Draw meshes
***/
void drawMeshes(glm::mat4 &proj_view)
{
    for(auto &m : ThreadSafeQueue::getMeshes(MESH))
    {
        m->draw(GL_TRIANGLES, var::mainShader, proj_view);
    }
}

void outlineMesh(glm::mat4 &proj_view)
{
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    var::outlineShader->use();
    glUniform1f(glGetUniformLocation(var::outlineShader->id, "outlining"), 1.004f);

    var::selectedMesh->draw(GL_TRIANGLES, var::outlineShader, proj_view);

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);
}

/***
 * Draw lights
***/
void drawLights(glm::mat4 &proj_view)
{
    for(auto &m : ThreadSafeQueue::getMeshes(LIGHT))
    {
        m->draw(GL_TRIANGLES, var::lightShader, proj_view);
    }
}

/***
 * Draw axes
***/
void drawAxes(glm::mat4 &proj_view, const glm::vec3 &location, const glm::vec3 &scale)
{
    static bool init = false;
    for(auto &m : ThreadSafeQueue::getMeshes(AXIS))
    {
        m->moveTo(location);
        m->draw(GL_TRIANGLES, var::axisShader, proj_view);
    }
    init = true;
}
/***
 * Function for loading all the shaders
***/
void loadShaders()
{
    /* Load mainShader for drawing */
    std::cout << "Compiling shaders" << std::endl;
    load_shader("../res/mainv.glsl", "../res/mainf.glsl", var::mainShader);
    load_shader("../res/lightv.glsl", "../res/lightf.glsl", var::lightShader);
    load_shader("../res/axisv.glsl", "../res/axisf.glsl", var::axisShader);
    load_shader("../res/outlinev.glsl", "../res/outlinef.glsl", var::outlineShader);
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
    load_texture("../res/img.png", var::defaultTexture);
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

void createAxes()
{
    objLoader::loadObjModel("../res/Basics/OX.obj", var::oxArr);
    objLoader::loadObjModel("../res/Basics/OY.obj", var::oyArr);
    objLoader::loadObjModel("../res/Basics/OZ.obj", var::ozArr);
}


/***
 * Separate function for mesh loading, so we can do this parallel to main thread
***/
void loadMeshData(std::string& path, std::vector<float>& verticesArray)
{
    objLoader::loadObjModel(path.c_str(), verticesArray);
}

/***
 * User can enter path to new file he would like to load (and only that so far)
***/
void listen()
{
    std::string path;
    while (!Window::isShouldClose())
    {
        std::cin >> path;
        std::cout << path << std::endl;
        std::cout << "Start loading mesh " << path << std::endl;
        std::thread loader(loadMeshData, std::ref(path), std::ref(var::tempArray));
        loader.join();
        std::cout << "Mesh " << path << "was loaded with vertex size :" << var::tempArray.size() << std::endl;
    }
}

void setUp()
{
    std::shared_ptr<Mesh> ox = std::make_shared<Mesh>(var::oxArr.data(), var::oxArr.size() / 8, attrs);
    std::shared_ptr<Mesh> oy = std::make_shared<Mesh>(var::oyArr.data(), var::oyArr.size() / 8, attrs);
    std::shared_ptr<Mesh> oz = std::make_shared<Mesh>(var::ozArr.data(), var::ozArr.size() / 8, attrs);

    ox->scale(glm::vec3(10, 10, 10));
    oy->scale(glm::vec3(10, 10, 10));
    oz->scale(glm::vec3(10, 10, 10));

    ThreadSafeQueue::push(ox, AXIS);
    ThreadSafeQueue::push(oy, AXIS);
    ThreadSafeQueue::push(oz, AXIS);

    std::shared_ptr<Mesh> faceMesh = std::make_shared<Mesh>(var::faceArray.data(), var::faceArray.size() / 8, attrs, var::faceTexture);
    std::shared_ptr<Mesh> hairMesh = std::make_shared<Mesh>(var::hairArray.data(), var::hairArray.size() / 8, attrs, var::hairTexture);
    std::shared_ptr<Mesh> lightMesh = std::make_shared<Mesh>(var::cubeArray.data(), var::cubeArray.size() / 8, attrs);

    /* Setting meshes default positions */     /*       x           z           y      */
    lightMesh->moveTo(glm::vec3(-23.1508, 115.151, 146.096));
    faceMesh->scale(glm::vec3(100, 100, 100));
    hairMesh->scale(glm::vec3(100, 100, 100));

    /* Appending meshes vector */
    ThreadSafeQueue::push(faceMesh, MESH);
    ThreadSafeQueue::push(hairMesh, MESH);
    ThreadSafeQueue::push(lightMesh, LIGHT);
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
        max = (int) ThreadSafeQueue::getMeshes(ALL).size() - 1;
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
        /* Move lights */
        if (EventsHandler::pressed(GLFW_KEY_Y))
        {
            var::selectedMesh->translate(glm::vec3(0, delta * speed, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_I))
        {
            var::selectedMesh->translate(glm::vec3(0, -delta * speed, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_U))
        {
            var::selectedMesh->translate(glm::vec3(0, 0, - delta * speed));
        }
        if (EventsHandler::pressed(GLFW_KEY_H))
        {
            var::selectedMesh->translate(glm::vec3(-delta * speed, 0, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_K))
        {
            var::selectedMesh->translate(glm::vec3(delta * speed, 0, 0));
        }
        if (EventsHandler::pressed(GLFW_KEY_J))
        {
            var::selectedMesh->translate(glm::vec3(0, 0, delta * speed));
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
            var::selectedMesh->scale(glm::vec3(1.01, 1.01, 1.01));
        }
        if (EventsHandler::pressed(GLFW_KEY_KP_SUBTRACT))
        {
            var::selectedMesh->scale(glm::vec3(.99, .99, .99));
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
            var::selectedMesh->rotate(currentRotationAxis, delta * rotationSpeed);
            var::selectedMesh->rotate(currentRotationAxis, delta * rotationSpeed);
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


        if (!var::tempArray.empty())
        {
            std::shared_ptr<Mesh> temp = std::make_shared<Mesh>(var::tempArray.data(), var::tempArray.size() / 8, attrs, var::defaultTexture);
            temp->scale(glm::vec3(100, 100, 100));
            ThreadSafeQueue::push(temp, MESH);
            var::tempArray.clear();
        }

        /* Camera projection view */
        glm::mat4 proj_view = camera->getProjection() * camera->getView();

        /* World draw */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.05f,0.05f,0.1f,1);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        /* Apply lighting data to mainShader */
        var::mainShader->use();
        var::mainShader->uniform3f("proj_pos", camera->position.x, camera->position.y, camera->position.z);
        var::mainShader->uniform3f("light_pos",
                                   ThreadSafeQueue::getMeshes(LIGHT)[0]->pos.x,
                                   ThreadSafeQueue::getMeshes(LIGHT)[0]->pos.y,
                                   ThreadSafeQueue::getMeshes(LIGHT)[0]->pos.z
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
        drawAxes(proj_view, var::selectedMesh->pos, var::selectedMesh->sc);

        /* Outlining selected object */
        outlineMesh(proj_view);

        /* Swapping buffers and pulling user inputs */
        Window::swapBuffers();
        EventsHandler::pullEvents();
    }
    Window::terminate();
}