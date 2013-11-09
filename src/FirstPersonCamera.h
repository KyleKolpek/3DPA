#ifndef FIRSTPERSONCAMERA_H
#define FIRSTPERSONCAMERA_H

#include "Camera.h"
#include "GLM/gtc/quaternion.hpp"

class FirstPersonCamera: public Camera
{
public:
    FirstPersonCamera();

    void rotateX(float degrees);
    void rotateY(float degrees);
    void rotateZ(float degrees);

    void moveTowardsAt(float distance);
    void strafeRight(float distance);

private:
    glm::quat rotation;
};

#endif
