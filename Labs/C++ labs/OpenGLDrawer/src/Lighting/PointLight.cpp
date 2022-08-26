//
// Created by Anton on 11.08.2022.
//

#include "PointLight.h"
#include "../Logging/easylogging++.h"

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
PointLight::PointLight(const glm::vec3 &pos, const glm::vec3 &amb, const glm::vec3 &diff, const glm::vec3 &spec, float con, float lin, float quad) :
        position(pos), constant(con), linear(lin), quadratic(quad), ambient(amb), diffuse(diff), specular(spec) {}

void PointLight::Display() const
{
    LOG(WARNING) << "\nPosition: " << position.x << "; " << position.y << "; " << position.z << ";" <<
                 "\nAmbient" << ambient.x << "; " << ambient.y << "; " << ambient.z << ";" <<
                 "\nDiffuse: " << diffuse.x << "; " << diffuse.y << "; " << diffuse.z << ";" <<
                 "\nSpecular: " << specular.x << "; " << specular.y << "; " << specular.z << ";" <<
                 "\nLinear: " << linear <<
                 "\nQuadratic: " << quadratic <<
                 "\nConstant" << constant;
}
