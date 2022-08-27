//
// Created by Anton on 14.08.2022.
//

#ifndef GRAPHICS_ACTOR_H
#define GRAPHICS_ACTOR_H


#include "../include/OpenGL/include/glm/glm.hpp"
#include "../include/OpenGL/include/glm/gtc/matrix_transform.hpp"
#include "../include/OpenGL/include/glm/gtx/transform.hpp"
#include "../Render/Shader.h"

class Actor
{
protected:
    glm::vec3 front, up, right, dir, position, scale, rotation;
    glm::mat4 model;

    virtual void Update() = 0;
public:

    /**
     * Creates Actor class, initializing fields to default values
     */
    Actor();
    virtual ~Actor() = default;

    /**
     * Change mesh position
     * @param deltaMove three dimensional vector of position change at every axis
     */
    void Translate(const glm::vec3& deltaMove);

    /**
     * Rotate mesh on deltaRotation degrees (in radians)
     * @param deltaRotation three dimensional vector of rotation
     */
    void Rotate(const glm::vec3 &deltaRotation);

    /**
     * Change mesh scale
     * @param deltaScale three dimensional vector of scale change at every axis
     */
    void Scale(const glm::vec3& deltaScale);

    /**
     * Change mesh position
     * @param newLocation three dimensional vector of new position at every axis
     */
    void MoveTo(const glm::vec3& newLocation);

    /**
     * Change mesh rotation
     * @param newRotation three dimensional vector of new rotation at every axis (in radians)
     */
    void RotateTo(const glm::vec3& newRotation);

    /**
     * Change mesh scale
     * @param newScale three dimensional vector of new scale at every axis
     */
    void ScaleTo(const glm::vec3& newScale);

    /**
     * Returns actor position
     * @return xyz position vector
     */
    glm::vec3 GetPosition();

    /**
     * Returns actor scale
     * @return xyz scale vector
     */
    glm::vec3 GetScale();

    /**
     * Returns actor rotation
     * @return xyz rotation vector
     */
    glm::vec3 GetRotation();

    /**
     * Returns actor direction
     * @return direction vector
     */
    glm::vec3 GetDirection();

    /**
     * Returns actor front vector
     * @return front vector
     */
    glm::vec3 GetFront();

    /**
     * Returns actor right vector
     * @return right vector
     */
    glm::vec3 GetRight();

    /**
     * Draws actor
     * @param shader shader to be applied for drawing
     */
    virtual void Draw(const Shader& shader) {};

    /**
     * Updates actor based on user inputs
     */
    virtual void UpdateControls() {};

    /**
     * Custom modifiable function, called every frame
     */
    virtual void Tick() {};
};


#endif //GRAPHICS_ACTOR_H
