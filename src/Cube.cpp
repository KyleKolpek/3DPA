#include <iostream>
#include "Cube.h"
#include "ShaderManager.h"

using namespace std;
float Cube::vertexData[] = { 0.0,  1.0,  0.0, // BACK  // TOP LEFT VERT
                             0.0,  0.0,  0.0,          // BOT LEFT VERT
                             1.0,  1.0,  0.0,          // TOP RIGHT VERT
                             1.0,  0.0,  0.0,          // BOT RIGHT VERT
                             1.0,  1.0,  0.0, // RIGHT
                             1.0,  0.0,  0.0,
                             1.0,  1.0, -1.0,
                             1.0,  0.0, -1.0,
                             1.0,  1.0, -1.0, // FRONT
                             1.0,  0.0, -1.0,
                             0.0,  1.0, -1.0,
                             0.0,  0.0, -1.0,
                             0.0,  1.0, -1.0, // LEFT
                             0.0,  0.0, -1.0,
                             0.0,  1.0,  0.0,
                             0.0,  0.0,  0.0,
                             0.0,  1.0,  0.0, // TOP
                             1.0,  1.0,  0.0,
                             0.0,  1.0, -1.0,
                             1.0,  1.0, -1.0,
                             0.0,  0.0,  0.0, // BOTTOM
                             0.0,  0.0, -1.0,
                             1.0,  0.0,  0.0,
                             1.0,  0.0, -1.0,
                                              // NORMALS
                             0.0,  0.0,  1.0, // BACK
                             0.0,  0.0,  1.0,
                             0.0,  0.0,  1.0,
                             0.0,  0.0,  1.0,
                             1.0,  0.0,  0.0, // RIGHT
                             1.0,  0.0,  0.0,
                             1.0,  0.0,  0.0,
                             1.0,  0.0,  0.0,
                             0.0,  0.0, -1.0, // FRONT
                             0.0,  0.0, -1.0,
                             0.0,  0.0, -1.0,
                             0.0,  0.0, -1.0,
                            -1.0,  0.0,  0.0, // LEFT
                            -1.0,  0.0,  0.0,
                            -1.0,  0.0,  0.0,
                            -1.0,  0.0,  0.0,
                             0.0,  1.0,  0.0, // TOP
                             0.0,  1.0,  0.0,
                             0.0,  1.0,  0.0,
                             0.0,  1.0,  0.0,
                             0.0, -1.0,  0.0, // BOTTOM
                             0.0, -1.0,  0.0,
                             0.0, -1.0,  0.0,
                             0.0, -1.0,  0.0,
                                              // COLOR (PER INSTANCE)
                             0.1,  0.8,  0.0, // 1
                             0.8,  0.0,  0.0, // 2
                             0.8,  0.5,  0.0, // 3
                             0.0,  0.0,  0.8, // 4
                             0.8,  0.8,  0.0, // 5
                             0.8,  0.8,  0.8, // 6

                             0.0,  0.0,  0.0, // 1
                             2.0,  2.0,  1.0, // 2
                            -2.0,  0.0,  0.0, // 3
                            -1.0,  2.0, -2.0, // 4
                             2.0, -2.0, -1.0, // 5
                            -1.0, -1.0, -1.0};// 6

int Cube::vertexCount = 4 * 6;



Cube::Cube(int x, int y, int z, int size):
    x(x),
    y(y),
    z(z),
    size(size)
{
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    setShaderManager(new ShaderManager("../assets/shaders/"));

    // pre-compile the shader
    //shaderManager->getProgram(2, "simple.vert", "simple.frag");
}

Cube::~Cube()
{
}

// TODO: Move this to renderer.
GLuint Cube::loadShader()
{
   return shaderManager->getProgram(2, "phongCube.vert", "phongCube.frag");
}

void Cube::draw(GLuint program)
{
    GLuint vertexPosLoc = glGetAttribLocation(program, "vertexPosition");
    GLuint vertexNormalLoc = glGetAttribLocation(program, "vertexNormal");
    GLuint vertexColorLoc = glGetAttribLocation(program, "vertexColor");
    GLuint cubePosLoc = glGetAttribLocation(program, "cubePosition");

    if(vertexPosLoc == -1)
    {
        cerr << "Error: Cannot find vertexPosition location" << endl;
        return;
    }
    if(vertexNormalLoc == -1)
    {
        cerr << "Error: Cannot find vertexNormal location" << endl;
        return;
    }
    if(vertexColorLoc == -1)
    {
        cerr << "Error: Cannot find vertexColor location" << endl;
        return;
    }

    glEnableVertexAttribArray(vertexPosLoc);
    glEnableVertexAttribArray(vertexNormalLoc);
    glEnableVertexAttribArray(vertexColorLoc);
    glEnableVertexAttribArray(cubePosLoc);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // TODO: Change this to be described by the ModelData struct
    glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), 0);
    glVertexAttribPointer(vertexNormalLoc, 3, GL_FLOAT, GL_TRUE,
        3 * sizeof(float), (void *)(vertexCount * 3 * sizeof(float)));
    glVertexAttribPointer(vertexColorLoc, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void *)(2 * vertexCount * 3 * sizeof(float)));
    glVertexAttribPointer(cubePosLoc, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void *)((2 * vertexCount + 6) * 3 * sizeof(float)));
    
    glVertexAttribDivisor(vertexColorLoc, 1);
    glVertexAttribDivisor(cubePosLoc, 1);

    // TODO: Change GL_TRIANGLES to account for modelData->vertexType
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, vertexCount, 6);
    glDisableVertexAttribArray(vertexPosLoc);
    glDisableVertexAttribArray(vertexNormalLoc);
    glDisableVertexAttribArray(vertexColorLoc);
    glDisableVertexAttribArray(cubePosLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
