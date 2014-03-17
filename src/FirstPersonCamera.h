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

    void moveUpDiscretely(int units);
    void moveForwardDiscretely(int units);
    void strafeRightDiscretely(int units);

    virtual void handleInput(InputMap &input);
private:
    glm::quat rotation;
    bool moveDiscretely;
    uint8_t lastMoved;
};

#endif
