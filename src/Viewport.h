#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "FirstPersonCamera.h"

class Viewport
{
public:
    Viewport(int width, int height);
    ~Viewport();
    FirstPersonCamera& getCurrentCamera();
protected:
    FirstPersonCamera camera;
    int width;
    int height;
};

#endif
