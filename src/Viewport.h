#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Camera.h"

class Viewport
{
public:
    Viewport(int width, int height);
    ~Viewport();
    Camera const& getCurrentCamera();
protected:
    Camera camera;
    int width;
    int height;
};

#endif
