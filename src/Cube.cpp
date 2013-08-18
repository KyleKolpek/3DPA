#include <iostream>
#include "Cube.h"
#include "ShaderManager.h"

using namespace std;
float Cube::vertexData[] = {0.0, 1.0,  0.0, // BACK  // TOP LEFT VERT
                            0.0, 0.0,  0.0,          // BOT LEFT VERT
                            1.0, 0.0,  0.0,          // BOT RIGHT VERT
                            1.0, 0.0,  0.0,          // BOT RIGHT VERT
                            1.0, 1.0,  0.0,          // TOP RIGHT VERT
                            0.0, 1.0,  0.0,          // TOP LEFT VERT
                            1.0, 1.0,  0.0, // RIGHT
                            1.0, 0.0,  0.0,
                            1.0, 0.0, -1.0,
                            1.0, 0.0, -1.0,
                            1.0, 1.0, -1.0,
                            1.0, 1.0,  0.0,
                            1.0, 1.0, -1.0, // FRONT
                            1.0, 0.0, -1.0,
                            0.0, 0.0, -1.0,
                            0.0, 0.0, -1.0,
                            0.0, 1.0, -1.0,
                            1.0, 1.0, -1.0,
                            0.0, 1.0, -1.0, // LEFT
                            0.0, 0.0, -1.0,
                            0.0, 0.0,  0.0,
                            0.0, 0.0,  0.0,
                            0.0, 1.0,  0.0,
                            0.0, 1.0, -1.0,
                            0.0, 1.0,  0.0, // TOP
                            1.0, 1.0,  0.0,
                            1.0, 1.0, -1.0,
                            1.0, 1.0, -1.0,
                            0.0, 1.0, -1.0,
                            0.0, 1.0,  0.0,
                            0.0, 0.0,  0.0, // BOT
                            0.0, 0.0, -1.0,
                            1.0, 0.0, -1.0,
                            1.0, 0.0, -1.0,
                            1.0, 0.0,  0.0,
                            0.0, 0.0,  0.0};

int Cube::vertexCount = 6 * 2 * 3;



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

void Cube::draw()
{
    GLuint program = shaderManager->getProgram(2, "simple.vert", "simple.frag");
    glUseProgram(program);

    GLuint vertexPosLoc = glGetAttribLocation(program, "vertexPosition");
    
    if(vertexPosLoc == -1)
    {
        cerr << "Error: Could not find vertexPosition attribute" << endl;
        return;
    }

    glEnableVertexAttribArray(vertexPosLoc);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), 0);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glDisableVertexAttribArray(vertexPosLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}
