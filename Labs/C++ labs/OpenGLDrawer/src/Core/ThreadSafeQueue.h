//
// Created by Anton on 20.12.2021.
//

#ifndef GRAPHICS_THREADSAFEQUEUE_H
#define GRAPHICS_THREADSAFEQUEUE_H

#include <memory>
#include <mutex>
#include <queue>
#include "../draw/Mesh.h"
#include "../lights/PointLight.h"
#include "../lights/DirectionalLight.h"
#include "PerspectiveCamera.h"

enum meshType
{
    MESH,
    LIGHT,
    AXIS,
    UI,
    ALL
};

enum lightType
{
    pLIGHT,
    sLIGHT,
    dLight
};

enum defaultMeshType
{
    CUBE,
    SPHERE,
    PLANE
};

class ThreadSafeQueue
{
private:
    static std::vector<std::shared_ptr<Mesh>> all;
    static std::vector<std::shared_ptr<Mesh>> axis;
    static std::vector<std::shared_ptr<Mesh>> meshes;
    static std::vector<std::shared_ptr<Mesh>> lights;
    static std::shared_ptr<DirectionalLight> dLights;
    static std::unique_ptr<PerspectiveCamera> pCamera;
    static std::vector<std::shared_ptr<PointLight>> pLights;
    static std::shared_ptr<Mesh> cube, sphere, plane;
    static std::mutex m;
public:

    static std::vector<std::shared_ptr<Mesh>>& GetMeshes(meshType id);
    static std::vector<std::shared_ptr<PointLight>>& GetPointLights();
    static std::shared_ptr<DirectionalLight>& GetDirectionalLight();
    static std::unique_ptr<PerspectiveCamera>& GetPlayerCamera();

    static void UnregisterMesh(const std::shared_ptr<Mesh>& ref);

    static void RegisterLight(const std::shared_ptr<PointLight> &light);
    static void RegisterPlayerCamera(const glm::vec3& position, float fov);
    static void RegisterMesh(const std::shared_ptr<Mesh>& mesh, meshType id);
    static void RegisterDefaultMesh(const std::shared_ptr<Mesh>& mesh, defaultMeshType id);
    static void RegisterLight(const std::shared_ptr<DirectionalLight> &light);
};


#endif //GRAPHICS_THREADSAFEQUEUE_H
