//
// Created by Anton on 12.08.2022.
//

#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H


#include "Texture.h"

class Material
{
private:
    std::shared_ptr<Texture> normal;
    std::shared_ptr<Texture> diffuse;
    std::shared_ptr<Texture> specular;

    float shininess;

public:
    explicit Material(const std::string& diff);
    explicit Material(std::shared_ptr<Texture> diff);

    Material(const std::string& diff, float shininess);

    Material(const std::string& diff, const std::string& spec);
    Material(const std::string& diff, const std::string& spec, float s);

    float GetShininess();
    std::shared_ptr<Texture> GetDiffuse();
    std::shared_ptr<Texture> GetSpecular();
};


#endif //GRAPHICS_MATERIAL_H
