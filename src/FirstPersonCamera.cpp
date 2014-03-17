#include "FirstPersonCamera.h"
#include "GLM/gtx/rotate_vector.hpp"
#include <iostream>

FirstPersonCamera::FirstPersonCamera():
    Camera(),
    rotation(),
    moveDiscretely(false)
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

// TODO: implement this
void FirstPersonCamera::strafeRightDiscretely(int units)
{
        glm::vec3 x = glm::vec3(1.0, 0.0, 0.0);
        glm::vec3 z = glm::vec3(0.0, 0.0, 1.0);
        glm::vec3 ae = at - eye;
        float xComp = glm::dot(x, ae);
        float zComp = glm::dot(z, ae);

        float delta;
        // strafe moves along minor axis
        // Strafe along X axis
        if(glm::abs(zComp) > glm::abs(xComp))
        {
            if(zComp > 0)
            {
                units = -units;
            }
            delta = (glm::floor(eye.x) + 0.5 + units) - eye.x;
            moveEye(glm::vec3(delta, 0.0, 0.0));
            moveAt(glm::vec3(delta, 0.0, 0.0));
        }
        // Strafe along Z axis
        else //(xComp >= zComp)
        {
            if(xComp <= 0)
            {
                units = -units;
            }
            delta = (glm::floor(eye.z) + 0.5 + units) - eye.z;
            moveEye(glm::vec3(0.0, 0.0, delta));
            moveAt(glm::vec3(0.0, 0.0, delta));
        }
        
}

void FirstPersonCamera::moveForwardDiscretely(int units)
{
        glm::vec3 x = glm::vec3(1.0, 0.0, 0.0);
        glm::vec3 z = glm::vec3(0.0, 0.0, 1.0);
        glm::vec3 ae = at - eye;
        float xComp = glm::dot(x, ae);
        float zComp = glm::dot(z, ae);

        float delta;
        // forward/back moves along major axis
        // Move along Z axis
        if(glm::abs(zComp) > glm::abs(xComp))
        {
            if(zComp <= 0)
            {
                units = -units;
            }
            delta = (glm::floor(eye.z) + 0.5 + units) - eye.z;
            moveEye(glm::vec3(0.0, 0.0, delta));
            moveAt(glm::vec3(0.0, 0.0, delta));
        }
        // Move along X axis
        else //(zComp => xComp)
        {
            if(xComp <= 0)
            {
                units = -units;
            }
            delta = (glm::floor(eye.x) + 0.5 + units) - eye.x;
            moveEye(glm::vec3(delta, 0.0, 0.0));
            moveAt(glm::vec3(delta, 0.0, 0.0));
        }
}

void FirstPersonCamera::handleInput(InputMap &input)
{
    double x = input.ranges[Input::RANGE_ROTATE_CAMERA_X];
    double y = input.ranges[Input::RANGE_ROTATE_CAMERA_Y];

    if(input.actions.find(Input::ACTION_MOVE_DISCRETELY) != input.actions.end())
    {
        moveDiscretely = !moveDiscretely;
    }
    if(input.states.find(Input::STATE_CAMERA_ROTATE) != input.states.end())
    {
        rotateY(-x);
        rotateX(y);
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_FORWARD) != input.states.end())
    {
        if(moveDiscretely)
        {
            moveForwardDiscretely(1);
        }
        else
        {
            moveTowardsAt(0.25);
        }
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_BACK) != input.states.end())
    {
        if(moveDiscretely)
        {
            moveForwardDiscretely(-1);
        }
        else
        {
            moveTowardsAt(-0.25);
        }
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_LEFT) != input.states.end())
    {
        if(moveDiscretely)
        {
            strafeRightDiscretely(-1);
        }
        else
        {
            strafeRight(-0.25);
        }
    }
    if(input.states.find(Input::STATE_CAMERA_MOVE_RIGHT) != input.states.end())
    {
        if(moveDiscretely)
        {
            strafeRightDiscretely(1);
        }
        else
        {
            strafeRight(0.25);
        }
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
