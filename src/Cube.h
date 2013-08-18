#ifndef CUBE_H
#define CUBE_H

#include "Drawable.h"
#include "stdgl.h"

class Model;

class Cube: public Drawable
{
public:
    Cube(int x, int y, int z, int size);
    ~Cube();
    void draw();
protected:
    int x;
    int y;
    int z;
    int size;
    static float vertexData[];
    static int vertexCount;
    GLuint vertexBuffer;
};                                                    
                                                      
#endif                                                
