#include "FirstPersonCamera.h"
#include "GLM/gtx/rotate_vector.hpp"
#include <iostream>

FirstPersonCamera::FirstPersonCamera():
    Camera(),
    rotation()
{
}

FirstPersonCamera::~FirstPersonCamera()
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

void FirstPersonCamera::handleInput(InputMap &input)
{
    double x = input.ranges[Input::RANGE_ROTATE_CAMERA_X];
    double y = input.ranges[Input::RANGE_ROTATE_CAMERA_Y];

    if(input.states.find(Input::STATE_CAMERA_ROTATE) != input.states.end())
    {
        rotateY(-x);
        rotateX(y);
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_FORWARD) != input.states.end())
    {
        moveTowardsAt(0.25);
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_BACK) != input.states.end())
    {
        moveTowardsAt(-0.25);
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_LEFT) != input.states.end())
    {
        strafeRight(-0.25);
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_RIGHT) != input.states.end())
    {
        strafeRight(0.25);
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_UP) != input.states.end())
    {
        moveEye(glm::vec3(0.0, 0.25, 0.0));
        moveAt(glm::vec3(0.0, 0.25, 0.0));
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_DOWN) != input.states.end())
    {
        moveEye(glm::vec3(0.0, -0.25, 0.0));
        moveAt(glm::vec3(0.0, -0.25, 0.0));
    }
}
