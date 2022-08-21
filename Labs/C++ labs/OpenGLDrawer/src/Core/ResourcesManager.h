//
// Created by Anton on 20.12.2021.
//

#ifndef GRAPHICS_RESOURCESMANAGER_H
#define GRAPHICS_RESOURCESMANAGER_H

#include <memory>
#include <mutex>
#include <queue>
#include <map>
#include "../Render/Model.h"
#include "../Lighting/PointLight.h"
#include "../Lighting/DirectionalLight.h"
#include "PerspectiveCamera.h"

class ResourcesManager
{
private:
    static std::shared_ptr<DirectionalLight> dLights;
    static std::unique_ptr<PerspectiveCamera> pCamera;
    static std::vector<std::shared_ptr<PointLight>> pLights;
    static std::map<std::string, std::shared_ptr<Model>> models;
    static std::map<std::string, std::shared_ptr<Shader>> shaders;
    static std::mutex m;
public:

    static vector<std::shared_ptr<Model>> & GetModels();
    static std::unique_ptr<PerspectiveCamera>& GetPlayerCamera();
    static std::shared_ptr<DirectionalLight>& GetDirectionalLight();
    static std::shared_ptr<Model> GetModel(const std::string &name);
    static std::shared_ptr<Shader> GetShader(const std::string &name);
    static std::vector<std::shared_ptr<PointLight>>& GetPointLights();

    static void RegisterModel(const std::string &name, const std::string &path);
    static void RegisterModel(const std::shared_ptr<Model>& model, std::string& name);

    static void RegisterLight(const std::shared_ptr<PointLight> &light);
    static void RegisterLight(const std::shared_ptr<DirectionalLight> &light);

    static void RegisterShader(const std::string &name, std::shared_ptr<Shader> &shader);
    static void RegisterShader(const std::string &name, const std::string &vFile, const std::string &fFile);

    static void RegisterPlayerCamera(const glm::vec3& position, float fov);
};


#endif //GRAPHICS_RESOURCESMANAGER_H
