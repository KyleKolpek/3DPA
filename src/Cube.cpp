#include <iostream>
#include "Cube.h"
#include "ShaderManager.h"

using namespace std;

Cube::Cube(int x, int y, int z, int size):
    x(x),
    y(y),
    z(z),
    size(size)
{
    // pre-compile the shader
    //shaderManager->getProgram(2, "simple.vert", "simple.frag");
}

Cube::~Cube()
{
}

