//
// Created by Anton on 14.08.2022.
//

#ifndef GRAPHICS_ACTOR_H
#define GRAPHICS_ACTOR_H


#include "../OpenGL/include/glm/glm.hpp"
#include "../OpenGL/include/glm/gtc/matrix_transform.hpp"
#include "../OpenGL/include/glm/gtx/transform.hpp"

class Actor
{
protected:
    glm::vec3 front, up, right, dir, position, scale, rotation;
    glm::mat4 model;

    virtual void Update();
public:
    void Translate(const glm::vec3& deltaMove);
    void Rotate(const glm::vec3 &deltaRotation);
    void Scale(const glm::vec3& deltaScale);
    void MoveTo(const glm::vec3& newLocation);
    void RotateTo(const glm::vec3& newRotation);
    void ScaleTo(const glm::vec3& newScale);

    glm::vec3 GetPosition();
    glm::vec3 GetScale();
    glm::vec3 GetRotation();
    glm::vec3 GetDirection();
    glm::vec3 GetFront();
    glm::vec3 GetRight();

    virtual void UpdateControls();
};


#endif //GRAPHICS_ACTOR_H
