//
// Created by Anton on 11.08.2022.
//

#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H


#include "../draw/Mesh.h"

class Light
{
public:
    std::shared_ptr<Mesh> mesh;
    void draw(unsigned int mode, const glm::mat4& proj_view);
};


#endif //GRAPHICS_LIGHT_H
