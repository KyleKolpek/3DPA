#include "ThirdPersonCamera.h"
#include "GLM/gtx/rotate_vector.hpp"
#include <iostream>

ThirdPersonCamera::ThirdPersonCamera():
    Camera(),
    rotation()
{
}

void ThirdPersonCamera::rotateX(float degrees)
{
    // TODO: Add a 'right' member to avoid excess cross products
    setAt(glm::rotate(at - eye, degrees,
        glm::cross(glm::normalize(at - eye), up)) + eye);
}

void ThirdPersonCamera::rotateY(float degrees)
{
    setAt(glm::rotate(at - eye, degrees, up) + eye);
}

void ThirdPersonCamera::rotateZ(float degrees)
{
    setAt(glm::rotateZ(at - eye, degrees) + eye);
}

void ThirdPersonCamera::moveTowardsAt(float distance)
{
    glm::vec3 delta = glm::normalize(at - eye) * distance;
    eye = eye + delta;
    at  = at + delta;
    viewMatrix = glm::lookAt(eye, at, up);
}

void ThirdPersonCamera::strafeRight(float distance)
{
    glm::vec3 delta = glm::cross(glm::normalize(at - eye), up) * distance;
    eye = eye + delta;
    at  = at + delta;
    viewMatrix = glm::lookAt(eye, at, up);
}
