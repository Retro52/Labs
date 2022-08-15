//
// Created by Anton on 14.08.2022.
//

#include "Global.h"
#include "../loaders/objLoader.h"

double Global::lastTime = 0.0;
double Global::deltaTime = 0.0;

bool Global::shouldDrawMesh = true, Global::shouldDrawLights = true, Global::shouldDrawAxis = false, Global::shouldDrawOutline = true;
std::shared_ptr<Mesh> Global::cube, Global::sphere;
std::shared_ptr<Material> Global::defaultMaterial;
std::shared_ptr<Shader> Global::mainShader, Global::lightShader, Global::outlineShader, Global::axisShader;

/**
 * Initializes OpenGl, creates window and sets settings for events handler
 */
void Global::Initialize()
{
    lastTime = 0.0;
    deltaTime = 0.0;

    glfwSwapInterval(0);

    // creating main window
    if(!Window::init(1920, 1080, "OpenGL drawer project"))
    {
        /* Replace with logging */
        LOG(INFO) << "OpenGL was successfully initialized, window created";
    }
    else
    {
        LOG(FATAL) << "Error during OpenGL initialization";
    }

    // setting key and mouse callbacks
    if (!EventsHandler::init())
    {
        LOG(INFO) << "Events handler initialized" << std::endl;
    }

    // loading default display shaders
    if(!Global::LoadShaders())
    {
        LOG(INFO) << "All shaders successfully loaded";
    }
    else
    {
        LOG(FATAL) << "Error while loading shaders";
    }

    // loading default materials
    Global::LoadMaterials();

    // loading default meshes
    if(!Global::LoadMeshes())
    {
        LOG(INFO) << "All default meshes successfully loaded";
    }
    else
    {
        LOG(ERROR) << "Error while loading default meshes";
    }

    // registering world camera
    ThreadSafeQueue::RegisterPlayerCamera(glm::vec3(0, 0, 10), glm::radians(90.0f));

    // setting directional light
    ThreadSafeQueue::RegisterLight(
            std::make_shared<DirectionalLight>(
                    glm::vec3(-0.2f, -1.0f, -0.3f),
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(0.5f, 0.5f, 0.5f)));
    // register point light
    ThreadSafeQueue::RegisterLight(
            std::make_shared<PointLight>(
                    glm::vec3(0.0f, 0.0f, 20.0f),
                    glm::vec3(0.05f, 0.05f, 0.05f),
                    glm::vec3(0.8f, 0.8f, 0.8f),
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    1.0f, 0.09f, 0.032f));
}

/**
 * Loads all default things like settings, controls, basic meshes, shaders, textures, etc.
 * @param path path to .ini file with settings
 */
void Global::Load(const std::string &path)
{
    LOG(WARNING) << "Not implemented yet\n";
}

/**
 * Global tick function
 */
void Global::Tick()
{
    /* Updating delta time */
    double curTime = glfwGetTime();
    deltaTime = curTime - lastTime;
    lastTime = curTime;

    /* Debug features */
    if(EventsHandler::justPressed(GLFW_KEY_1))
    {
        shouldDrawLights = !shouldDrawLights;
    }
    if (EventsHandler::justPressed(GLFW_KEY_2))
    {
        shouldDrawMesh = !shouldDrawMesh;
    }
    if (EventsHandler::justPressed(GLFW_KEY_3))
    {
        shouldDrawAxis = !shouldDrawAxis;
    }
    if (EventsHandler::justPressed(GLFW_KEY_4))
    {
        shouldDrawOutline = !shouldDrawOutline;
    }

    /* Update camera controls */
    ThreadSafeQueue::GetPlayerCamera()->UpdateControls();
    /* Update window controls */
    Window::Tick();
}

/**
 * Returns last frame delta time
 * @return world delta time
 */
double Global::GetWorldDeltaTime()
{
    return deltaTime;
}

/**
 * Loads default shaders
 */
int Global::LoadShaders()
{
    if(Shader::load_shader("../res/mainv.glsl", "../res/mainf.glsl", mainShader)
    || Shader::load_shader("../res/lightv.glsl", "../res/lightf.glsl", lightShader)
    || Shader::load_shader("../res/outlinev.glsl", "../res/outlinef.glsl", outlineShader)
    || Shader::load_shader("../res/axisv.glsl", "../res/axisf.glsl", axisShader))
    {
        return -1;
    }
    return 0;
}

int Global::LoadMaterials()
{
    defaultMaterial = std::make_shared<Material>("../res/img.png");
    return 0;
}

int Global::LoadMeshes()
{
    std::vector<int> attributes({3, 2, 3, 0});
    std::vector<float> temp;

    int res = 0;

    if (!(res += objLoader::loadObjModel("../res/Basics/sphere.obj", temp)))
    {
        ThreadSafeQueue::RegisterDefaultMesh(std::make_shared<Mesh>(temp.data(), temp.size() / 8, attributes, mainShader, defaultMaterial), SPHERE);
    }
    if (!(res += objLoader::loadObjModel("../res/Basics/cube.obj", temp)))
    {
        ThreadSafeQueue::RegisterDefaultMesh(std::make_shared<Mesh>(temp.data(), temp.size() / 8, attributes, mainShader, defaultMaterial), CUBE);
    }
    if (!(res += objLoader::loadObjModel("../res/Basics/plane.obj", temp)))
    {
        ThreadSafeQueue::RegisterDefaultMesh(std::make_shared<Mesh>(temp.data(), temp.size() / 8, attributes, mainShader, defaultMaterial), PLANE);
        ThreadSafeQueue::RegisterMesh(std::make_shared<Mesh>(temp.data(), temp.size() / 8, attributes, mainShader, defaultMaterial), MESH);
        ThreadSafeQueue::GetMeshes(MESH)[0]->ScaleTo(glm::vec3(1000.0f, 1000.0f, 1000.0f));
    }
    return res;
}

/* TODO: create camera class, so we can draw either orthographic or perspective camera */
void Global::Draw(const std::unique_ptr<PerspectiveCamera> &camera)
{
    glm::mat4 proj_view = camera->getProjection() * camera->getView();
    glm::vec3 lightColor(1, 1, 1);

    // TODO: replace with skybox
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.429f, 0.625f, 0.938f,1);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);

    std::shared_ptr<DirectionalLight> dirLight = ThreadSafeQueue::GetDirectionalLight();

    // apply data to main shader
    mainShader->use();
    mainShader->uniform3f("proj_pos", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
    mainShader->uniform1b("shouldCalcLight", shouldDrawLights);

    mainShader->uniformnpl(ThreadSafeQueue::GetPointLights());
//    mainShader->uniform1dl(ThreadSafeQueue::GetDirectionalLight());

    mainShader->uniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
//        mainShader->uniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    mainShader->uniform3f("dirLight.ambient", 0.15f, 0.15f, 0.15f);
    mainShader->uniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    mainShader->uniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
    defaultMaterial->diffuse->bind();
    // draw meshes
    if (shouldDrawMesh)
    {
        for(auto &m : ThreadSafeQueue::GetMeshes(MESH))
        {
            m->draw(GL_TRIANGLES, proj_view);
        }
    }

    // draw lights
    if (shouldDrawLights)
    {
        lightShader->use();
        lightShader->uniform3f("v_color", lightColor.r, lightColor.g, lightColor.b);

        for(auto &m : ThreadSafeQueue::GetMeshes(LIGHT))
        {
            m->draw(GL_TRIANGLES, proj_view);
        }
    }

    // draw the rest
    if (shouldDrawAxis)
    {
        axisShader->use();
        axisShader->uniform3f("v_color", lightColor.r, lightColor.g, lightColor.b);

        for(auto &m : ThreadSafeQueue::GetMeshes(AXIS))
        {
//            m->MoveTo(location);
//            m->ScaleTo(scale);
            m->draw(GL_TRIANGLES, proj_view);
        }
    }
}

void Global::EndFrame()
{
    /* Swapping OpenGL buffers and pulling this frame events */
    Window::swapBuffers();
    EventsHandler::pullEvents();
}
