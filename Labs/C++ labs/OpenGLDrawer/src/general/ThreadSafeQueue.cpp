//
// Created by Anton on 20.12.2021.
//

#include <iostream>
#include "ThreadSafeQueue.h"
#include "ThreadSafeQueueFields.h"

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
    }
}

void ThreadSafeQueue::push(const std::shared_ptr<Mesh>& mesh, meshType id)
{
    std::cout << "Adding mesh to active mesh pool" << std::endl;
    if (id == MESH)
    {
        ThreadSafeQueue::m.lock();
        ThreadSafeQueue::meshes.push_back(mesh);
        ThreadSafeQueue::m.unlock();
    }
    else if (id == LIGHT)
    {
        ThreadSafeQueue::m.lock();
        ThreadSafeQueue::lights.push_back(mesh);
        ThreadSafeQueue::m.unlock();
    }
    std::cout << "Mesh was successfully added to active mesh pool" << std::endl;
}
