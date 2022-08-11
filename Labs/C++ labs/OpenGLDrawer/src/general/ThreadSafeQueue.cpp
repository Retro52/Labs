//
// Created by Anton on 20.12.2021.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "ThreadSafeQueue.h"
#include "ThreadSafeQueueFields.h"

/**
 * Creates a std:vector containing all meshes registered at the game for selected type (basicly lights or other)
 * @param id meshType enum id for mesh type: LIGHT for all emissive surfaces and MESH for all the rest
 * @return std::vector with all necessary meshes
 */
std::vector<std::shared_ptr<Mesh>> &ThreadSafeQueue::getMeshes(meshType id)
{
    {
        if (id == MESH)
        {
            return ThreadSafeQueue::meshes;
        }
        else if (id == LIGHT)
        {
            return ThreadSafeQueue::lights;
        }
        else if (id == AXIS)
        {
            return ThreadSafeQueue::axis;
        }
        else if(id == ALL)
        {
            all.clear();
            all.reserve(lights.size() + meshes.size());
            all.insert(all.end(), lights.begin(), lights.end());
            all.insert(all.end(), meshes.begin(), meshes.end());
            return all;
        }
    }
}

/**
 * Adds new mesh to the queue
 * @param mesh mesh to add
 * @param id mesh type
 */
void ThreadSafeQueue::push(const std::shared_ptr<Mesh>& mesh, meshType id)
{
    std::cout << "Adding mesh to active mesh pool" << std::endl;
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
    std::cout << "Mesh was successfully added to active mesh pool" << std::endl;
}

/**
 * Deletes mesh from queue
 * @param ref std::shared_ptr of mesh reference
 */
void ThreadSafeQueue::remove(const std::shared_ptr<Mesh>& ref)
{
    ThreadSafeQueue::m.lock();
    auto newEnd = std::remove(meshes.begin(), meshes.end(), ref);
    meshes.erase(newEnd, meshes.end());
    ThreadSafeQueue::m.unlock();
}
