//
// Created by Anton on 14.08.2022.
//

#include "Global.h"
#include "Config.h"
#include "../UI/UIHandler.h"

double Global::lastTime;
double Global::deltaTime;
double Global::elapsedTime;

int Global::curFPS, Global::drawMode = 1;

long Global::frame;


std::string drawModeToString(int drawMode)
{
    switch (drawMode)
    {
        case 1:
            return "Lit";
        case 2:
            return "Unlit";
        case 3:
            return "Lighting Only";
        case 4:
            return "Normal map lighting test";
        default:
            return std::to_string(drawMode);
    }
}

/**
 * Initializes OpenGl, creates window and sets settings for events handler
 */
void Global::Initialize()
{
    lastTime = 0.0;
    deltaTime = 0.0;
    elapsedTime = 0.0;
    curFPS = 0;

    LOG(INFO) << "Program initialization started";
    if (Config::Load("config.ini"))
    {
        LOG(INFO) << "Configs were successfully loaded";
    }
    else
    {
        LOG(ERROR) << "Couldn`t load configs";
        return;
    }


    // setting key and mouse callbacks
    if (!EventsHandler::init())
    {
        LOG(INFO) << "Events handler initialized" << std::endl;
    }


    if(!UIHandler::Initialize())
    {
        LOG(INFO) << "UI handler successfully initialized";
    }
    else
    {
        LOG(ERROR) << "UI handler was not initialized";
        return;
    }

    // registering world camera
    ResourcesManager::RegisterPlayerCamera(glm::vec3(0, 0, 5), glm::radians(90.0f));
    ResourcesManager::GetPlayerCamera()->Rotate(glm::vec3(0, 0, 1.57));

    // setting directional light
    ResourcesManager::RegisterLight(
            std::make_shared<DirectionalLight>(
                    glm::vec3(-0.2f, -1.0f, -0.3f),
                    glm::vec3(0.5f, 0.5f, 0.5f),
                    glm::vec3(0.5f, 0.5f, 0.5f),
                    glm::vec3(0.5f, 0.5f, 0.5f)));

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
    frame++;
    /* Updating delta time */
    double curTime = glfwGetTime();
    deltaTime = curTime - lastTime;
    lastTime = curTime;
    elapsedTime += deltaTime;

    if (elapsedTime >= 0.33)
    {
        curFPS = frame * 3;
        frame = 0;
        elapsedTime = 0.0;
    }

    /* Debug features */
    if(EventsHandler::justPressed(GLFW_KEY_1))
    {
        drawMode = 1;
    }
    if (EventsHandler::justPressed(GLFW_KEY_2))
    {
        drawMode = 2;
    }
    if (EventsHandler::justPressed(GLFW_KEY_3))
    {
        drawMode = 3;
    }
    if (EventsHandler::justPressed(GLFW_KEY_4))
    {
        drawMode = 4;
    }

    /* Update camera controls */
    ResourcesManager::GetPlayerCamera()->UpdateControls();
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


/* TODO: create camera class, so we can Render either orthographic or perspective camera */
void Global::Draw(const std::unique_ptr<PerspectiveCamera> &camera)
{
    glm::mat4 projView = camera->getProjection() * camera->getView();
    
    glm::vec3 lightColor(1, 1, 1);

    // TODO: replace with skybox
    glClearColor(0.203f, 0.76f, 0.938f,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//    glStencilFunc(GL_ALWAYS, 1, 0xFF);
//    glStencilMask(0xFF);


    std::shared_ptr<DirectionalLight> dirLight = ResourcesManager::GetDirectionalLight();

    std::shared_ptr<Shader> lightShader = ResourcesManager::GetShader("lightShader");
    std::shared_ptr<Shader> mainShader = ResourcesManager::GetShader("mainShader");
    std::shared_ptr<Shader> uiShader = ResourcesManager::GetShader("uiShader");

    for(auto &m : ResourcesManager::GetModels())
    {
        // apply data to main shader
        mainShader->use();
        mainShader->setInt("drawMode", drawMode);
        mainShader->setMat4("view", camera->getView());
        mainShader->setMat4("projection", camera->getProjection());
        mainShader->setVec3("ProjPos", camera->GetPosition());
        mainShader->setDirLight(ResourcesManager::GetDirectionalLight());
        mainShader->setPointLights(ResourcesManager::GetPointLights());

        m->Draw(* mainShader);
    }

    UIHandler::RenderText(* uiShader, "FPS: " + std::to_string(curFPS), 0.0f, (float) Window::getHeight() - 24.0f, 1.0, glm::vec3(1.0, 1.0, 1.0));
    UIHandler::RenderText(* uiShader, "Position: " + std::to_string(camera->GetPosition().x) + "; " + std::to_string(camera->GetPosition().y) + "; " + std::to_string(camera->GetPosition().z), 0.0f, (float) Window::getHeight() - 48.0f, 1.0, glm::vec3(1.0, 1.0, 1.0));
    UIHandler::RenderText(* uiShader, "Direction: " + std::to_string(camera->GetDirection().x) + "; " + std::to_string(camera->GetDirection().y) + "; " + std::to_string(camera->GetDirection().z), 0.0f, (float) Window::getHeight() - 72.0f, 1.0, glm::vec3(1.0, 1.0, 1.0));
    UIHandler::RenderText(* uiShader, "View mode: " + drawModeToString(drawMode), 0.0f, (float) Window::getHeight() - 96.0f, 1.0, glm::vec3(1.0, 1.0, 0.0));
}

void Global::EndFrame()
{
    /* Swapping OpenGL buffers and pulling this frame events */
    Window::swapBuffers();
    EventsHandler::pullEvents();
}
