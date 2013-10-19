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
    GLuint loadShader();
    void draw(GLuint program);
    int x;
    int y;
    int z;
    int size;

private:
    static float vertexData[];
    static int vertexCount;
    GLuint vertexBuffer;
};                                                    
                                                      
#endif                                                
