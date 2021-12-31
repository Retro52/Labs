//
// Created by Anton on 28.12.2021.
//

#ifndef GRAPHICS_FUNCTIONS_H
#define GRAPHICS_FUNCTIONS_H

/*TODO: replace with vector; move to variables namespace*/
#include "loaders/objLoader.h"

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

/* Outline selected mesh */
void outlineMesh(glm::mat4 &proj_view)
{
    if (!var::selectedMesh)
    {
        std::cerr << "Selected mesh is NULLPTR, might be updated next frame";
        return;
    }
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
        m->MoveTo(location);
        m->ScaleTo(scale);
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

    ox->Scale(glm::vec3(10, 10, 10));
    oy->Scale(glm::vec3(10, 10, 10));
    oz->Scale(glm::vec3(10, 10, 10));

    ThreadSafeQueue::push(ox, AXIS);
    ThreadSafeQueue::push(oy, AXIS);
    ThreadSafeQueue::push(oz, AXIS);

    std::shared_ptr<Mesh> faceMesh = std::make_shared<Mesh>(var::faceArray.data(), var::faceArray.size() / 8, attrs, var::faceTexture);
    std::shared_ptr<Mesh> hairMesh = std::make_shared<Mesh>(var::hairArray.data(), var::hairArray.size() / 8, attrs, var::hairTexture);
    std::shared_ptr<Mesh> lightMesh = std::make_shared<Mesh>(var::cubeArray.data(), var::cubeArray.size() / 8, attrs);

    /* Setting meshes default positions */     /*       x           z           y      */
    lightMesh->MoveTo(glm::vec3(-23.1508, 115.151, 146.096));
    faceMesh->Scale(glm::vec3(100, 100, 100));
    hairMesh->Scale(glm::vec3(100, 100, 100));

    /* Appending meshes vector */
    ThreadSafeQueue::push(faceMesh, MESH);
    ThreadSafeQueue::push(hairMesh, MESH);
    ThreadSafeQueue::push(lightMesh, LIGHT);
}

#endif //GRAPHICS_FUNCTIONS_H
