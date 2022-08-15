//
// Created by Anton on 12.08.2022.
//

#include "Material.h"

#include <utility>
#include "../logging/easylogging++.h"

Material::Material(std::shared_ptr<Texture> diffuse) : diffuse(std::move(diffuse)), shininess(1.0f) {}

Material::Material(std::shared_ptr<Texture> diffuse, float s) : Material(std::move(diffuse))
{
    shininess = s;
}

Material::Material(const std::string& diff) : shininess(1.0f)
{
    if (Texture::load_texture(diff, diffuse))
    {
        LOG(ERROR) << "Error loading default texture: " << diff;
    }
    else
    {
        LOG(INFO) << diff << " : material successfully created";
    }
}

Material::Material(const std::string& diffuse, float s) : Material(diffuse)
{
    shininess = s;
}