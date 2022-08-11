//
// Created by Anton on 11.08.2022.
//

#include "PointLight.h"

/**
 * Point light constructor
 * @deprecated
 * @param pos
 * @param con
 * @param lin
 * @param quad
 * @param amb
 * @param diff
 * @param spec
 */
PointLight::PointLight(const glm::vec3& pos, float con, float lin, float quad, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec) :
        position(pos), constant(con), linear(lin), quadratic(quad), ambient(amb), diffuse(diff), specular(spec) {}

PointLight::PointLight(const glm::vec3 &pos, float con, float lin, float quad, const glm::vec3 &amb, const glm::vec3 &diff, const glm::vec3 &spec, const std::shared_ptr<Mesh> &m) :
        PointLight(pos, con, lin, quad, amb, diff, spec)
{
    mesh = m;
}
