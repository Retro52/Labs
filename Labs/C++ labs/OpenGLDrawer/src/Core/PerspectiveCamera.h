//
// Created by Anton on 12.12.2021.
//

#ifndef GRAPHICS_PERSPECTIVECAMERA_H
#define GRAPHICS_PERSPECTIVECAMERA_H

#include "../include/OpenGL/include/glm/glm.hpp"
#include "Actor.h"
#include <iostream>

class PerspectiveCamera : public Actor
{
public:
    /**
     * Camera constructor
     * @param position camera position
     * @param fov camera field of view (60 - 100 range is recommended)
     */
    PerspectiveCamera(const glm::vec3& position, float fov);

    /**
     * Updates camera matrices every frame
     */
    void Update() override;

    /**
     * Updates camera based on the inputs
     */
    void UpdateControls() override;

    /**
     * Get camera projection matrix
     * @return projection matrix
     */
    glm::mat4 GetProjection();

    /**
     * Get camera view matrix
     * @return view matrix
     */
    glm::mat4 GetView();

    /**
     * Set new field of view
     * @param newFOV new field of view, in degrees
     */
    void SetFieldOfView(float newFOV);

    /**
     * Get camera field of view
     * @return vield of view, in degrees
     */
    float GetFieldOfView() const;
private:
    float fov, zoom;
    double posX, posY;

};

#endif //GRAPHICS_PERSPECTIVECAMERA_H
