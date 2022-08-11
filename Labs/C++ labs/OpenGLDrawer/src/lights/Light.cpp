//
// Created by Anton on 11.08.2022.
//

#include "Light.h"

void Light::draw(unsigned int mode, const glm::mat4& proj_view)
{
    if (mesh)
    {
        mesh->draw(mode, proj_view);
    }
}
