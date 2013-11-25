#include <iostream>
#include <ctime>
#include <cstdlib>
#include "CubeGenerator.h"

using namespace std;

CubeGenerator::CubeGenerator():
    position(0.0, 0.0, 0.0),
    cubeManager(NULL)
{
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Cube::vertexCount * 3 * 2,
        Cube::vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //setShaderManager(new ShaderManager("../assets/shaders/"));
    srand(time(NULL));
}

CubeGenerator::~CubeGenerator()
{
    glDeleteBuffers(1, &vertexBuffer);
}

GLuint CubeGenerator::loadShader()
{
   return shaderManager->getProgram(2, "phongCubeRGBA.vert",
                                    "phongCubeRGBA.frag");
}

void CubeGenerator::draw(GLuint program)
{
    CubePosColorAlpha instanceData;
    instanceData.position[0] = glm::floor(position.x);
    instanceData.position[1] = glm::floor(position.y);
    instanceData.position[2] = glm::ceil(position.z);
    
    instanceData.color[0] = 1;
    instanceData.color[1] = 1;
    instanceData.color[2] = 1;

    instanceData.alpha = .25;

    glGenBuffers(1, &instanceBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubePosColorAlpha),
        &instanceData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


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
    if(cubePosLoc == -1)
    {
        cerr << "Error: Cannot find cubePos location" << endl;
        return;
    }

    glEnableVertexAttribArray(vertexPosLoc);
    glEnableVertexAttribArray(vertexNormalLoc);
    glEnableVertexAttribArray(cubePosLoc);
    glEnableVertexAttribArray(vertexColorLoc);

    // Vertex Data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // TODO: Change this to be described by the ModelData struct
    glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), 0);
    glVertexAttribPointer(vertexNormalLoc, 3, GL_FLOAT, GL_TRUE,
        3 * sizeof(float), (void *)(Cube::vertexCount * 3 * sizeof(float)));

    // Instance data
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
    glVertexAttribPointer(cubePosLoc, 3, GL_FLOAT, GL_FALSE,
        7 * sizeof(float), 0);
    glVertexAttribPointer(vertexColorLoc, 4, GL_FLOAT, GL_FALSE,
        7 * sizeof(float), (void *)( 3 * sizeof(float)));
    
    glVertexAttribDivisor(cubePosLoc, 1);
    glVertexAttribDivisor(vertexColorLoc, 1);

    // TODO: Change GL_TRIANGLES to account for modelData->vertexType
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, Cube::vertexCount, 1);

    glVertexAttribDivisor(cubePosLoc, 0);
    glVertexAttribDivisor(vertexColorLoc, 0);
    glDisableVertexAttribArray(vertexPosLoc);
    glDisableVertexAttribArray(vertexNormalLoc);
    glDisableVertexAttribArray(cubePosLoc);
    glDisableVertexAttribArray(vertexColorLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &instanceBuffer);
}

void CubeGenerator::move(glm::vec3 delta)
{
    position += delta;
}

void CubeGenerator::moveTo(glm::vec3 position)
{
    this->position = position;
}

void CubeGenerator::addCube()
{
    Cube c;
    c.x = glm::floor(position.x);
    c.y = glm::floor(position.y);
    c.z = glm::ceil(position.z);

    c.red   = float(rand())/float(RAND_MAX);
    c.green = float(rand())/float(RAND_MAX);
    c.blue  = float(rand())/float(RAND_MAX);

    if(!cubeManager->insert(c))
    {
        cubeManager->erase(c.x, c.y, c.z);
    }
}

void CubeGenerator::removeCube()
{
    
}

glm::vec3 CubeGenerator::getPosition()
{
    return position;
}

void CubeGenerator::handleInput(InputMap &input)
{
    if(input.actions.find(Input::ACTION_ADD_CUBE) != input.actions.end())
    {
        addCube();
    }
}
