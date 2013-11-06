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

void Camera::moveTowardsAt(float distance)
{
    this->eye += glm::normalize(at - eye) * distance;
    viewMatrix = glm::lookAt(this->eye, this->at, this->up);
}

void Camera::rotate(float degrees, glm::vec3 const &axis)
{
    glm::mat4 t = glm::translate(glm::mat4(1.0), -at);
    glm::mat4 ti = glm::translate(glm::mat4(1.0), at);
    glm::mat4 tirt = ti * glm::rotate(t, degrees, axis);
    setEye(glm::vec3(tirt * glm::vec4(eye, 1.0)));
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

void Camera::update(float sec)
{
    // ADD CAMERA MOVEMENT HERE
    float cameraMoveDistance = camSpeed * sec;
    
    /*if( input.IsKeyDown(sf::Key::Left ) )
    {
        moveEye(glm::vec3( cameraMoveDistance*(-1.0), 0.0, 0.0 ));
        moveAt(glm::vec3( cameraMoveDistance*(-1.0), 0.0, 0.0 ));
    }
    else if( input.IsKeyDown(sf::Key::Right) )
    {
        moveEye(glm::vec3( cameraMoveDistance, 0.0, 0.0 ));
        moveAt(glm::vec3( cameraMoveDistance, 0.0, 0.0 ));
    }
    if( input.IsKeyDown(sf::Key::Up ))
    {
        moveEye(glm::vec3( 0.0, 0.0, cameraMoveDistance*(-1.0) ));
        moveAt(glm::vec3( 0.0, 0.0, cameraMoveDistance*(-1.0) ));
    }
    else if( input.IsKeyDown(sf::Key::Down ))
    {
        moveEye(glm::vec3( 0.0, 0.0, cameraMoveDistance ));
        moveAt(glm::vec3( 0.0, 0.0, cameraMoveDistance ));
    }
    if( input.IsKeyDown(sf::Key::PageUp) )
    {
        moveTowardsAt( cameraMoveDistance );
    }
    else if( input.IsKeyDown(sf::Key::PageDown) )
    {
        moveTowardsAt( cameraMoveDistance*(-1.0) );
    }*/
}
