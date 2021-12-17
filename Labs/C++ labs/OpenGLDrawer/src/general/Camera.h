//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

#include "../OpenGL/include/glm/glm.hpp"

class Camera
{
private:
    void Update();

public:
    glm::mat4 rotation;

    glm::vec3 front, up, right, dir, position;

    float fov, zoom;

    Camera(const glm::vec3& position, float fov);

    void rotate(float x, float y, float z);

    glm::mat4 getProjection() const;
    glm::mat4 getView() const;
};

#endif //GRAPHICS_CAMERA_H
