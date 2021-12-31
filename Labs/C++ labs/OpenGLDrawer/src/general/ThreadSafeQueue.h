//
// Created by Anton on 20.12.2021.
//

#ifndef GRAPHICS_THREADSAFEQUEUE_H
#define GRAPHICS_THREADSAFEQUEUE_H

#include <memory>
#include <mutex>
#include <queue>
#include "../draw/Mesh.h"

enum meshType
{
    MESH, LIGHT, AXIS, ALL
};
class ThreadSafeQueue;

class ThreadSafeQueue
{
public:

    static std::vector<std::shared_ptr<Mesh>> meshes;
    static std::vector<std::shared_ptr<Mesh>> lights;
    static std::vector<std::shared_ptr<Mesh>> axis;
    static std::vector<std::shared_ptr<Mesh>> all;
    static std::mutex m;

    static std::vector<std::shared_ptr<Mesh>>& getMeshes(meshType id);
    static void remove(const std::shared_ptr<Mesh>& ref);

    static void push(const std::shared_ptr<Mesh>& mesh, meshType id);
};


#endif //GRAPHICS_THREADSAFEQUEUE_H
