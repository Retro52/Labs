//
// Created by Anton on 11.08.2022.
//

#include "DirectionalLight.h"

/**
 *
 * @param dir
 * @param amb
 * @param diff
 * @param spec
 */
DirectionalLight::DirectionalLight(const glm::vec3& dir, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec) : direction(dir), ambient(amb), diffuse(diff), specular(spec){}

DirectionalLight::DirectionalLight(const glm::vec3 &dir, const glm::vec3 &amb, const glm::vec3 &diff, const glm::vec3 &spec, const std::shared_ptr<Mesh>& m) : DirectionalLight(dir, amb, diff, spec)
{
    mesh = m;
}
