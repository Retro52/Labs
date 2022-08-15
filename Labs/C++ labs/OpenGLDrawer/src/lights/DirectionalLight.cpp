//
// Created by Anton on 11.08.2022.
//

#include "DirectionalLight.h"
#include "../logging/easylogging++.h"

/**
 *
 * @param dir
 * @param amb
 * @param diff
 * @param spec
 */
DirectionalLight::DirectionalLight(const glm::vec3& dir, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec) : direction(dir), ambient(amb), diffuse(diff), specular(spec){}

void DirectionalLight::Display() const
{
        LOG(WARNING) << "\nDirection: " << direction.x << "; " << direction.y << "; " << direction.z << ";" <<
                     "\nAmbient: " << ambient.x << "; " << ambient.y << "; " << ambient.z << ";" <<
                     "\nDiffuse: " << diffuse.x << "; " << diffuse.y << "; " << diffuse.z << ";" <<
                     "\nSpecular: " << specular.x << "; " << specular.y << "; " << specular.z << ";\n";
}

