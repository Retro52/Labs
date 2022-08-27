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
    /* Restriction to create an instance of this class */
    ResourcesManager() = delete;
    ResourcesManager(ResourcesManager&&) = delete;
    ResourcesManager(const ResourcesManager&) = delete;

    /**
     * Get list of registered actors
     * @return vector of the registered actors
     */
    static std::vector<std::unique_ptr<Actor>>& GetActors();

    /**
     * Get player current camera
     * @return pointer to the camera
     */
    static std::unique_ptr<PerspectiveCamera> & GetPlayerCamera();

    /**
     * Get scene directional light
     * @return pointer to the directional light
     */
    static std::unique_ptr<DirectionalLight> & GetDirectionalLight();

    /**
     * Get registered shader by name
     * @param name shader name
     * @return pointer to the shader
     */
    static Shader * GetShader(const std::string &name);

    /**
     * Get all scene point lights
     * @return vector of point lights
     */
    static std::vector<std::unique_ptr<PointLight>>& GetPointLights();

    /**
     * Register new actor from model class
     * @param name model name (@deprecated)
     * @param path path to the model
     */
    static void RegisterModel(const std::string &name, const std::string &path);

    /**
     * Register directional light
     * @param dir directional strength
     * @param amb ambient strength
     * @param diff diffuse strength
     * @param spec specular strength
     */
    static void RegisterLight(const glm::vec3& dir, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec);

    /**
     * Register new point light
     * @param pos position
     * @param amb ambient strength
     * @param diff diffuse strength
     * @param spec specular strength
     * @param con constant
     * @param lin linear
     * @param quad quadratic
     */
    static void RegisterLight(const glm::vec3 &pos, const glm::vec3 &amb, const glm::vec3 &diff, const glm::vec3 &spec, float con, float lin, float quad);

    /**
     * Register new shader
     * @param name shader name
     * @param vFile path to the vertex shader file
     * @param fFile path to the fragment shader file
     * @param gFile path to the geometry shader file (optional)
     */
    static void RegisterShader(const std::string &name, const std::string &vFile, const std::string &fFile, const std::string &gFile = "");

    /**
     * Register current player camera
     * @param position camera position
     * @param fov camera field of view
     */
    static void RegisterPlayerCamera(const glm::vec3& position, float fov);
};

#endif //GRAPHICS_RESOURCESMANAGER_H
