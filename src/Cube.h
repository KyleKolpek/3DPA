#ifndef CUBE_H
#define CUBE_H

#include "stdgl.h"

struct Cube
{
public:
    int x;
    int y;
    int z;
    float red;
    float green;
    float blue;
    float alpha;
    unsigned int size;

    static float vertexData[];
    static int vertexCount;
};                                                    
                                                      
#endif                                                
