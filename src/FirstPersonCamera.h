#ifndef FIRSTPERSONCAMERA_H
#define FIRSTPERSONCAMERA_H

#include "Camera.h"
#include "Updatable.h"
#include "GLM/gtc/quaternion.hpp"

class FirstPersonCamera: public Camera, public Updatable
{
public:
    FirstPersonCamera();
    ~FirstPersonCamera();

    void rotateX(float degrees);
    void rotateY(float degrees);
    void rotateZ(float degrees);

    void moveTowardsAt(float distance);
    void strafeRight(float distance);

    virtual void handleInput(InputMap &input);
private:
    glm::quat rotation;
};

#endif
