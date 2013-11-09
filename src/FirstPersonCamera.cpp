#include "FirstPersonCamera.h"
#include "GLM/gtx/rotate_vector.hpp"
#include <iostream>

FirstPersonCamera::FirstPersonCamera():
    Camera(),
    rotation()
{
}

void FirstPersonCamera::rotateX(float degrees)
{
    // TODO: Add a 'right' member to avoid excess cross products
    setAt(glm::rotate(at - eye, degrees,
        glm::cross(glm::normalize(at - eye), up)) + eye);
}

void FirstPersonCamera::rotateY(float degrees)
{
    setAt(glm::rotate(at - eye, degrees, up) + eye);
}

void FirstPersonCamera::rotateZ(float degrees)
{
    setAt(glm::rotateZ(at - eye, degrees) + eye);
}

void FirstPersonCamera::moveTowardsAt(float distance)
{
    glm::vec3 delta = glm::normalize(at - eye) * distance;
    eye = eye + delta;
    at  = at + delta;
    viewMatrix = glm::lookAt(eye, at, up);
}

void FirstPersonCamera::strafeRight(float distance)
{
    glm::vec3 delta = glm::cross(glm::normalize(at - eye), up) * distance;
    eye = eye + delta;
    at  = at + delta;
    viewMatrix = glm::lookAt(eye, at, up);
}
