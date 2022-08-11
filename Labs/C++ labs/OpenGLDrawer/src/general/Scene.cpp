//
// Created by Anton on 11.08.2022.
//

#include "Scene.h"

void Scene::DrawAll(glm::mat4 &proj_view)
{
    for (const auto& mesh : ThreadSafeQueue::getMeshes(MESH))
    {
        mesh->draw(GL_TRIANGLES, proj_view);
    }
    for (const auto& mesh : ThreadSafeQueue::getMeshes(LIGHT))
    {
        mesh->draw(GL_TRIANGLES, proj_view);
    }
    for (const auto& mesh : ThreadSafeQueue::getMeshes(AXIS))
    {
        mesh->draw(GL_TRIANGLES, proj_view);
    }
}
