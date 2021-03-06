#include "Camera.h"
#include "GLM/gtc/matrix_transform.hpp"
#include <iostream>

float Camera::camSpeed(25.0);

Camera::Camera():
    eye(0.0, 0.0, -1.0),
    at(0.0),
    up(0.0, 1.0, 0.0),
    viewMatrix(1.0),
    projMatrix(1.0)
{
}

Camera::Camera(glm::vec3 const &eye,
               glm::vec3 const &at,
               glm::vec3 const &up):
    eye(eye),
    at(at),
    up(up),
    viewMatrix(1.0),
    projMatrix(1.0)
{
    viewMatrix = glm::lookAt(eye, at, up);
}

glm::mat4 Camera::getViewMatrix() const
{
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return projMatrix;
}

void Camera::setAt(glm::vec3 const &at)
{
    this->at = at;
    viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::setEye(glm::vec3 const &eye)
{
    this->eye = eye;
    viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::setUp(glm::vec3 const &up)
{
    this->up = up;
    viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::moveAt(glm::vec3 const &at)
{
    this->at += at;
    viewMatrix = glm::lookAt(this->eye, this->at, this->up);
}

void Camera::moveEye(glm::vec3 const &eye)
{
    this->eye += eye;
    viewMatrix = glm::lookAt(this->eye, this->at, this->up);
}

void Camera::moveUp(glm::vec3 const &up)
{
    this->up += up;
    viewMatrix = glm::lookAt(this->eye, this->at, this->up);
}

glm::vec3 Camera::getAt() const
{
    return at;
}

glm::vec3 Camera::getEye() const
{
    return eye;
}

glm::vec3 Camera::getUp() const
{
    return up;
}

void Camera::perspective(float fov, float aspect, float zNear, float zFar)
{
    projMatrix = glm::perspective(fov, aspect, zNear, zFar);
}
