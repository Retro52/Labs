//
// Created by Anton on 11.08.2022.
//

#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H

#include <vector>
#include "../draw/Mesh.h"
#include "../Core/ThreadSafeQueue.h"

class Scene
{
    static void DrawAll(glm::mat4 &proj_view);
};


#endif //GRAPHICS_SCENE_H
