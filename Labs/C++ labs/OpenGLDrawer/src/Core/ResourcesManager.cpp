//
// Created by Anton on 20.12.2021.
//

#include <iostream>
#include <vector>
#include "ResourcesManager.h"
#include "../Logging/easylogging++.h"

std::unique_ptr<PerspectiveCamera> ResourcesManager::pCamera;
std::unique_ptr<DirectionalLight> ResourcesManager::dLights;
std::map<std::string, std::unique_ptr<Shader>> ResourcesManager::shaders;
std::vector<std::unique_ptr<Actor>> ResourcesManager::actors;
std::vector<std::unique_ptr<PointLight>> ResourcesManager::pLights;
std::mutex ResourcesManager::m;

void ResourcesManager::RegisterLight(const glm::vec3& dir, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec)
{
    const std::lock_guard<std::mutex> lock(m);
    dLights = std::make_unique<DirectionalLight> (dir, amb, diff, spec);
    LOG(INFO) << "Directional light was successfully set";
}

void ResourcesManager::RegisterLight(const glm::vec3 &pos, const glm::vec3 &amb, const glm::vec3 &diff, const glm::vec3 &spec, float con, float lin, float quad)
{
    const std::lock_guard<std::mutex> lock(m);
    pLights.push_back(std::make_unique<PointLight>(pos, amb, diff, spec, con, lin, quad));
    LOG(INFO) << "Point light was successfully added";
}

void ResourcesManager::RegisterPlayerCamera(const glm::vec3 &position, float fov)
{
    const std::lock_guard<std::mutex> lock(m);
    pCamera = std::make_unique<PerspectiveCamera>(position, fov);
    LOG(INFO) << "Player camera successfully created";
}

void ResourcesManager::RegisterShader(const std::string &name, const std::string &vFile, const std::string &fFile, const std::string &gFile)
{
    const std::lock_guard<std::mutex> lock(m);
    try
    {
        if (!gFile.empty())
        {
            shaders[name] = std::make_unique<Shader>(vFile.c_str(), fFile.c_str(), gFile.c_str());
        }
        else
        {
            shaders[name] = std::make_unique<Shader>(vFile.c_str(), fFile.c_str());
        }
        LOG(INFO) << "Shader " + name + " successfully registered";
    }
    catch(InGameException& e)
    {
        LOG(WARNING) << "Failed to register shader" << name << ". Reason: " << e.what();
    }
}


void ResourcesManager::RegisterModel(const std::string &name, const std::string &path)
{
    const std::lock_guard<std::mutex> lock(m);
    try
    {
        actors.push_back(std::make_unique<Model>(path));
        LOG(INFO) << "Actor " << name << " successfully registered";
    }
    catch (InGameException& e)
    {
        LOG(WARNING) << "Failed to register actor. Reason: " << e.what();
    }
}

std::unique_ptr<PerspectiveCamera>& ResourcesManager::GetPlayerCamera()
{
    return pCamera;
}

std::unique_ptr<DirectionalLight>& ResourcesManager::GetDirectionalLight()
{
    return dLights;
}

std::vector<std::unique_ptr<PointLight>>& ResourcesManager::GetPointLights()
{
    return pLights;
}

Shader * ResourcesManager::GetShader(const std::string& name)
{
    const std::lock_guard<std::mutex> lock(m);
#if __cplusplus >= 202002L
    if(!shaders.contains(name))
    {
        LOG(ERROR) << "Shader " + name + " is not registered at ResourcesManager";
        throw InGameException("Trying to receive unregistered shader");
    }
#else
    /* Count returns number of elements with specified key, so we can use it like bool (non 0 - present, 0 - absent) */
    if(!shaders.count(name))
    {
        LOG(ERROR) << "Shader " + name + " is not registered at ResourcesManager";
        throw InGameException("Trying to receive unregistered shader");
    }
#endif
    return shaders[name].get();
}

std::vector<std::unique_ptr<Actor>>& ResourcesManager::GetActors()
{
    return actors;
}
