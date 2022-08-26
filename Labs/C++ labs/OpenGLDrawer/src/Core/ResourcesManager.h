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
    static std::unique_ptr<DirectionalLight> dLights;
    static std::vector<std::unique_ptr<Actor>> actors;
    static std::unique_ptr<PerspectiveCamera> pCamera;
    static std::vector<std::unique_ptr<Model>> rModels;
    static std::vector<std::unique_ptr<PointLight>> pLights;
    static std::map<std::string, std::unique_ptr<Shader>> shaders;

    static std::mutex m;
public:
    static std::vector<std::unique_ptr<Actor>>& GetActors();
    static std::unique_ptr<PerspectiveCamera> & GetPlayerCamera();
    static std::unique_ptr<DirectionalLight> & GetDirectionalLight();
    static Shader * GetShader(const std::string &name);
    static std::vector<std::unique_ptr<PointLight>>& GetPointLights();

    static void RegisterModel(const std::string &name, const std::string &path);

    static void RegisterLight(const glm::vec3& dir, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec);
    static void RegisterLight(const glm::vec3 &pos, const glm::vec3 &amb, const glm::vec3 &diff, const glm::vec3 &spec, float con, float lin, float quad);

    static void RegisterShader(const std::string &name, const std::string &vFile, const std::string &fFile);

    static void RegisterPlayerCamera(const glm::vec3& position, float fov);
};

#endif //GRAPHICS_RESOURCESMANAGER_H
