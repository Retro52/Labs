//
// Created by Anton on 11.08.2022.
//

#include "Scene.h"

void Scene::DrawAll(glm::mat4 &proj_view)
{
    for (const auto& mesh : ThreadSafeQueue::GetMeshes(MESH))
    {
        mesh->draw(GL_TRIANGLES, proj_view);
    }
    for (const auto& mesh : ThreadSafeQueue::GetMeshes(LIGHT))
    {
        mesh->draw(GL_TRIANGLES, proj_view);
    }
    for (const auto& mesh : ThreadSafeQueue::GetMeshes(AXIS))
    {
        mesh->draw(GL_TRIANGLES, proj_view);
    }
}
