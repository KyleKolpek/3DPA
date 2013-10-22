#ifndef CUBE_H
#define CUBE_H

#include "Drawable.h"
#include "stdgl.h"

class Cube
{
public:
    Cube(int x, int y, int z, int size);
    ~Cube();
    GLuint loadShader();
    int x;
    int y;
    int z;
    float red;
    float green;
    float blue;
    int size;
};                                                    
                                                      
#endif                                                
