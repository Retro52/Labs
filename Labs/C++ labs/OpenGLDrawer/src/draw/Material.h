//
// Created by Anton on 12.08.2022.
//

#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H


#include "Texture.h"

class Material
{
public:
    std::shared_ptr<Texture> diffuse;
    std::shared_ptr<Texture> normal;
    std::shared_ptr<Texture> specular;

    float shininess;

    explicit Material(const std::string& diffuse);
    explicit Material(std::shared_ptr<Texture> diffuse);
    Material(std::shared_ptr<Texture> diffuse, float shininess);
    Material(const std::string& diffuse, float shininess);

};


#endif //GRAPHICS_MATERIAL_H
