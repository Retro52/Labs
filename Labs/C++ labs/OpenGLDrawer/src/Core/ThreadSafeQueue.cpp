//
// Created by Anton on 20.12.2021.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "ThreadSafeQueue.h"
#include "../logging/easylogging++.h"

std::vector<std::shared_ptr<Mesh>> ThreadSafeQueue::all;
std::vector<std::shared_ptr<Mesh>> ThreadSafeQueue::axis;
std::vector<std::shared_ptr<Mesh>> ThreadSafeQueue::meshes;
std::vector<std::shared_ptr<Mesh>> ThreadSafeQueue::lights;
std::shared_ptr<DirectionalLight> ThreadSafeQueue::dLights;
std::unique_ptr<PerspectiveCamera> ThreadSafeQueue::pCamera;
std::vector<std::shared_ptr<PointLight>> ThreadSafeQueue::pLights;
std::shared_ptr<Mesh> ThreadSafeQueue::cube, ThreadSafeQueue::sphere, ThreadSafeQueue::plane;

std::mutex ThreadSafeQueue::m;

/**
 * Creates a std:vector containing all meshes registered at the game for selected type (basicly lights or other)
 * @param id meshType enum id for mesh type: LIGHT for all emissive surfaces and MESH for all the rest
 * @return std::vector with all necessary meshes
 */
std::vector<std::shared_ptr<Mesh>>& ThreadSafeQueue::GetMeshes(meshType id)
{
    {
        switch (id)
        {
            case MESH:
                return ThreadSafeQueue::meshes;
            case LIGHT:
                return ThreadSafeQueue::lights;
            case AXIS:
                return ThreadSafeQueue::axis;
            case ALL:
                all.clear();
                all.reserve(lights.size() + meshes.size());
                all.insert(all.end(), lights.begin(), lights.end());
                all.insert(all.end(), meshes.begin(), meshes.end());
                return all;
            default:
                break;
        }
    }
}

std::vector<std::shared_ptr<PointLight>>& ThreadSafeQueue::GetPointLights()
{
    return pLights;
}

std::shared_ptr<DirectionalLight>& ThreadSafeQueue::GetDirectionalLight()
{
    return dLights;
}

/**
 * Adds new mesh to the queue
 * @param mesh mesh to add
 * @param id mesh type
 */
void ThreadSafeQueue::RegisterMesh(const std::shared_ptr<Mesh>& mesh, meshType id)
{
    ThreadSafeQueue::m.lock();
    if (id == MESH)
    {
        ThreadSafeQueue::meshes.push_back(mesh);
    }
    else if (id == LIGHT)
    {
        ThreadSafeQueue::lights.push_back(mesh);
    }
    else if (id == AXIS)
    {
        ThreadSafeQueue::axis.push_back(mesh);
    }
    ThreadSafeQueue::m.unlock();
    LOG(INFO) << "Another non-default mesh was successfully added to active mesh pool";
}

void ThreadSafeQueue::RegisterLight(const std::shared_ptr<DirectionalLight>& light)
{
    ThreadSafeQueue::m.lock();
    dLights = light;
    ThreadSafeQueue::m.unlock();
    LOG(INFO) << "Directional light was successfully set";
}

void ThreadSafeQueue::RegisterLight(const std::shared_ptr<PointLight>& light)
{
    ThreadSafeQueue::m.lock();
    pLights.push_back(light);
    ThreadSafeQueue::m.unlock();
    LOG(INFO) << "Point light was successfully added";
}

/**
 * Deletes mesh from queue
 * @param ref std::shared_ptr of mesh reference
 */
void ThreadSafeQueue::UnregisterMesh(const std::shared_ptr<Mesh>& ref)
{
    ThreadSafeQueue::m.lock();
    auto newEnd = std::remove(meshes.begin(), meshes.end(), ref);
    meshes.erase(newEnd, meshes.end());
    ThreadSafeQueue::m.unlock();
    LOG(INFO) << "Mesh was successfully unregistered";
}

void ThreadSafeQueue::RegisterPlayerCamera(const glm::vec3 &position, float fov)
{
    ThreadSafeQueue::m.lock();
    pCamera = std::make_unique<PerspectiveCamera>(position, fov);
    ThreadSafeQueue::m.unlock();
    LOG(INFO) << "Player camera successfully created";
}

void ThreadSafeQueue::RegisterDefaultMesh(const std::shared_ptr<Mesh> &mesh, defaultMeshType id)
{
    switch (id)
    {
        case CUBE:
            cube = mesh;
            break;
        case SPHERE:
            sphere = mesh;
            break;
        case PLANE:
            plane = mesh;
            break;
        default:
            break;
    }
    LOG(INFO) << "Default mesh: " << id << " was successfully added to active mesh pool";
}

std::unique_ptr<PerspectiveCamera> &ThreadSafeQueue::GetPlayerCamera()
{
    return pCamera;
}
