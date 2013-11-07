#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "ThirdPersonCamera.h"

class Viewport
{
public:
    Viewport(int width, int height);
    ~Viewport();
    ThirdPersonCamera& getCurrentCamera();
protected:
    ThirdPersonCamera camera;
    int width;
    int height;
};

#endif
