//
// Created by Anton on 20.12.2021.
//

#include <iostream>
#include <vector>
#include "ResourcesManager.h"
#include "../Logging/easylogging++.h"
#include <chrono>

std::unique_ptr<PerspectiveCamera> ResourcesManager::pCamera;
std::unique_ptr<DirectionalLight> ResourcesManager::dLights;
std::map<std::string, std::unique_ptr<Shader>> ResourcesManager::shaders;
std::map<std::string, std::unique_ptr<Model>> ResourcesManager::models;
std::vector<std::unique_ptr<PointLight>> ResourcesManager::pLights;
std::mutex ResourcesManager::m;

void ResourcesManager::RegisterLight(const glm::vec3& dir, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec)
{
    m.lock();
    dLights = std::make_unique<DirectionalLight> (dir, amb, diff, spec);
    m.unlock();
    LOG(INFO) << "Directional light was successfully set";
}

void ResourcesManager::RegisterLight(const glm::vec3 &pos, const glm::vec3 &amb, const glm::vec3 &diff, const glm::vec3 &spec, float con, float lin, float quad)
{
    m.lock();
    pLights.push_back(std::make_unique<PointLight>(pos, amb, diff, spec, con, lin, quad));
    m.unlock();
    LOG(INFO) << "Point light was successfully added";
}

void ResourcesManager::RegisterPlayerCamera(const glm::vec3 &position, float fov)
{
    m.lock();
    pCamera = std::make_unique<PerspectiveCamera>(position, fov);
    m.unlock();
    LOG(INFO) << "Player camera successfully created";
}

void ResourcesManager::RegisterShader(const std::string &name, const std::string &vFile, const std::string &fFile)
{
    m.lock();
    shaders[name] = std::make_unique<Shader>(vFile.c_str(), fFile.c_str());
    if (!shaders[name]->id)
    {
        shaders.erase(name);
        LOG(ERROR) << "Failed to load shader " << name << ", check log to see shader detailed errors";
    }
    m.unlock();
    LOG(INFO) << "Shader " + name + " successfully registered";
}


void ResourcesManager::RegisterModel(const std::string &name, const std::string &path)
{
    m.lock();
    models[name] = std::make_unique<Model>(path);
    if (models[name]->meshes.empty())
    {
        models.erase(name);
        LOG(WARNING) << "Model " << name << " was not registered because model is missing meshes";
    }
    m.unlock();
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
    m.lock();
#if __cplusplus >= 202002L
    if(!shaders.contains(name))
    {
        LOG(ERROR) << "Shader " + name + " is not registered at ResourcesManager";
        m.unlock();
        return nullptr;
    }
#else
    if(!shaders.count(name))
    {
        LOG(ERROR) << "Shader " + name + " is not registered at ResourcesManager";
        m.unlock();
        return nullptr;
    }
#endif
    m.unlock();
    return shaders[name].get();
}

Model * ResourcesManager::GetModel(const std::string& name)
{
    m.lock();
    /* TODO: rework return */
#if __cplusplus >= 202002L
    if(!models.contains(name))
    {
        LOG(ERROR) << "Model " + name + " is not registered at ResourcesManager";
        m.unlock();
        return nullptr;
    }
#else
    if(!models.count(name))
    {
        LOG(ERROR) << "Model " + name + " is not registered at ResourcesManager";
        m.unlock();
        return nullptr;
    }
#endif
    m.unlock();
    return models[name].get();
}

std::vector<Model *> ResourcesManager::GetModels()
{
    m.lock();
    std::vector<Model *> v;
    v.reserve(models.size());
    for(auto & model : models)
    {
        v.push_back(model.second.get());
    }
    m.unlock();
    return v;
}