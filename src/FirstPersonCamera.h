#ifndef THIRDPERSONCAMERA_H
#define THIRDPERSONCAMERA_H

#include "Camera.h"
#include "GLM/gtc/quaternion.hpp"

class ThirdPersonCamera: public Camera
{
public:
    ThirdPersonCamera();

    void rotateX(float degrees);
    void rotateY(float degrees);
    void rotateZ(float degrees);

    void moveTowardsAt(float distance);
    void strafeRight(float distance);

private:
    glm::quat rotation;
};

#endif
