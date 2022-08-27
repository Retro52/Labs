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
            return "Wireframe";
        case 5:
            return "Directional light only";
        case 6:
            return "Point light only";
        case 7:
            return "Specular map view";
        case 8:
            return "Normal map view";
        default:
            return std::to_string(drawMode);
    }
}

void Global::Initialize()
{
    lastTime = 0.0;
    deltaTime = 0.0;
    elapsedTime = 0.0;
    curFPS = 0;

    LOG(INFO) << "Program initialization started";

    try
    {
        Config::LoadIni("config.ini");
        EventsHandler::Initialize();
    }
    catch (InGameException& e)
    {
        LOG(FATAL) << "Error during program initialization. Reason: " << e.what();
        throw InGameException("Global initialization error");
    }
    EventsHandler::ToggleCursor();

    // registering world camera
    ResourcesManager::RegisterPlayerCamera(glm::vec3(0, 0, 5), glm::radians(90.0f));
    ResourcesManager::GetPlayerCamera()->Rotate(glm::vec3(0, 0, 1.57));

    // setting directional light
    ResourcesManager::RegisterLight(
                    glm::vec3(-0.2f, -1.0f, -0.3f),
                    glm::vec3(0.5f, 0.5f, 0.5f),
                    glm::vec3(0.5f, 0.5f, 0.5f),
                    glm::vec3(0.5f, 0.5f, 0.5f));

    ResourcesManager::RegisterLight(
            glm::vec3(0, 0, 3),
            glm::vec3(0.05f, 0.05f, 0.05f),
            glm::vec3(0.8f, 0.8f, 0.8f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            1.0f, 0.09f, 0.032f
            );
}

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
    if(EventsHandler::IsJustPressed(GLFW_KEY_1))
    {
        drawMode = 1;
    }
    if (EventsHandler::IsJustPressed(GLFW_KEY_2))
    {
        drawMode = 2;
    }
    if (EventsHandler::IsJustPressed(GLFW_KEY_3))
    {
        drawMode = 3;
    }
    if (EventsHandler::IsJustPressed(GLFW_KEY_4))
    {
        drawMode = 4;
    }
    if (EventsHandler::IsJustPressed(GLFW_KEY_5))
    {
        drawMode = 5;
    }
    if (EventsHandler::IsJustPressed(GLFW_KEY_6))
    {
        drawMode = 6;
    }
    if (EventsHandler::IsJustPressed(GLFW_KEY_7))
    {
        drawMode = 7;
    }
    if (EventsHandler::IsJustPressed(GLFW_KEY_8))
    {
        drawMode = 8;
    }
    if (EventsHandler::IsJustPressed(GLFW_KEY_9))
    {
        drawMode = 9;
    }
    if (EventsHandler::IsPressed(GLFW_KEY_KP_ADD))
    {
        ResourcesManager::GetPlayerCamera()->SetFieldOfView(ResourcesManager::GetPlayerCamera()->GetFieldOfView() - .01f);
    }
    if (EventsHandler::IsPressed(GLFW_KEY_KP_SUBTRACT))
    {
        ResourcesManager::GetPlayerCamera()->SetFieldOfView(ResourcesManager::GetPlayerCamera()->GetFieldOfView() + .01f);
    }

    /* Update camera controls */
    ResourcesManager::GetPlayerCamera()->UpdateControls();
    /* Update window controls */
    Window::Tick();
}

double Global::GetWorldDeltaTime()
{
    return deltaTime;
}

void Global::Draw(const std::unique_ptr<PerspectiveCamera> &camera)
{
    glm::mat4 projView = camera->GetProjection() * camera->GetView();

    glClearColor(0.203f, 0.76f, 0.938f,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader * mainShader = ResourcesManager::GetShader("mainShader");
    Shader * uiShader = ResourcesManager::GetShader("uiShader");

    if (drawMode == 4)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    for(auto &m : ResourcesManager::GetActors())
    {
        // apply data to main shader
        mainShader->Use();
        mainShader->setInt("drawMode", drawMode);
        mainShader->setMat4("view", camera->GetView());
        mainShader->setMat4("projection", camera->GetProjection());
        mainShader->setVec3("ProjPos", camera->GetPosition());
        mainShader->setDirLight(ResourcesManager::GetDirectionalLight());
        mainShader->setPointLights(ResourcesManager::GetPointLights());

        m->Tick();
        m->UpdateControls();
        m->Draw(* mainShader);

    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    UIHandler::RenderText(* uiShader, "FPS: " + std::to_string(curFPS), 0.0f, (float) Window::GetHeight() - 24.0f, 1.0, glm::vec3(1.0, 1.0, 1.0));
    UIHandler::RenderText(* uiShader, "View mode: " + drawModeToString(drawMode), 0.0f, (float) Window::GetHeight() - 48.0f, 1.0, glm::vec3(1.0, 1.0, 0.0));
    UIHandler::RenderText(* uiShader, "WASD to move, KeyPad +- to zoom in/out, 1-8 to switch view Modes", 0.0f, (float) Window::GetHeight() - 72.0f, 1.0, glm::vec3(1.0, 1.0, 1.0));
    UIHandler::RenderText(* uiShader, "FOV: " + std::to_string((ResourcesManager::GetPlayerCamera()->GetFieldOfView() / 3.1415) * 180), 0.0f, (float) Window::GetHeight() - 96.0f, 1.0, glm::vec3(1.0, 0.5, 0.5));
}

void Global::EndFrame()
{
    /* Swapping OpenGL buffers and pulling this frame events */
    Window::SwapBuffers();
    EventsHandler::PullEvents();
}
