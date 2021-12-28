//
// Created by Anton on 20.12.2021.
//

#ifndef GRAPHICS_THREADSAFEQUEUEFIELDS_H
#define GRAPHICS_THREADSAFEQUEUEFIELDS_H

#include "ThreadSafeQueue.h"

std::vector<std::shared_ptr<Mesh>> ThreadSafeQueue::all;
std::vector<std::shared_ptr<Mesh>> ThreadSafeQueue::axis;
std::vector<std::shared_ptr<Mesh>> ThreadSafeQueue::meshes;
std::vector<std::shared_ptr<Mesh>> ThreadSafeQueue::lights;
std::mutex ThreadSafeQueue::m;

#endif //GRAPHICS_THREADSAFEQUEUEFIELDS_H
