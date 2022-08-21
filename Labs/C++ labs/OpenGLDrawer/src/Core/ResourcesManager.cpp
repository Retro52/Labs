//
// Created by Anton on 20.12.2021.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "ResourcesManager.h"
#include "../Logging/easylogging++.h"


/* Adapted for updated resources manager */
std::shared_ptr<DirectionalLight> ResourcesManager::dLights;
std::unique_ptr<PerspectiveCamera> ResourcesManager::pCamera;
std::vector<std::shared_ptr<PointLight>> ResourcesManager::pLights;
std::map<std::string, std::shared_ptr<Shader>> ResourcesManager::shaders;
std::map<std::string, std::shared_ptr<Model>> ResourcesManager::models;
std::mutex ResourcesManager::m;

std::vector <std::shared_ptr<Model>> v;

std::vector<std::shared_ptr<PointLight>>& ResourcesManager::GetPointLights()
{
    return pLights;
}

std::shared_ptr<DirectionalLight>& ResourcesManager::GetDirectionalLight()
{
    return dLights;
}

void ResourcesManager::RegisterLight(const std::shared_ptr<DirectionalLight>& light)
{
    m.lock();
    dLights = light;
    m.unlock();
    LOG(INFO) << "Directional light was successfully set";
}

void ResourcesManager::RegisterLight(const std::shared_ptr<PointLight>& light)
{
    m.lock();
    pLights.push_back(light);
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

std::unique_ptr<PerspectiveCamera> &ResourcesManager::GetPlayerCamera()
{
    return pCamera;
}

void ResourcesManager::RegisterShader(const std::string &name, std::shared_ptr<Shader> &shader)
{
    m.lock();
    shaders[name] = shader;
    m.unlock();
    LOG(INFO) << "Shader " + name + " successfully registered";
}


void ResourcesManager::RegisterShader(const std::string &name, const std::string &vFile, const std::string &fFile)
{
    m.lock();
    shaders[name] = std::make_shared<Shader>(vFile.c_str(), fFile.c_str());
    m.unlock();
    LOG(INFO) << "Shader " + name + " successfully registered";
}

std::shared_ptr<Shader> ResourcesManager::GetShader(const std::string &name)
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
    return shaders[name];
}

void ResourcesManager::RegisterModel(const std::shared_ptr<Model> &model, std::string &name)
{
    m.lock();
    models[name] = model;
    m.unlock();
}

void ResourcesManager::RegisterModel(const std::string &name, const std::string &path)
{
    m.lock();
    models[name] = std::make_shared<Model>(path.c_str());
//    models[name]->MoveTo(glm::vec3(10, 10, 10));
//    models[name]->ScaleTo(glm::vec3(10, 10, 10));
    m.unlock();
}

std::shared_ptr<Model> ResourcesManager::GetModel(const std::string &name)
{
    m.lock();
#if __cplusplus >= 202002L
    if(!models.contains(name))
    {
        LOG(ERROR) << "Shader " + name + " is not registered at ResourcesManager";
        m.unlock();
        return nullptr;
    }
#else
    if(!models.count(name))
    {
        LOG(ERROR) << "Shader " + name + " is not registered at ResourcesManager";
        m.unlock();
        return nullptr;
    }
#endif
    m.unlock();
    return models[name];
}

std::vector<std::shared_ptr<Model>> & ResourcesManager::GetModels()
{
    m.lock();
    v.clear();
    for(auto & model : models)
    {
        v.push_back( model.second );
    }
    m.unlock();
    return v;
}
