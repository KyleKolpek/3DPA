#include "CubeManager.h"
#include "Model.h"
#include "ModelData.h"
#include <iostream>

using namespace std;

float CubeManager::vertexData[] = { 0.0,  1.0,  0.0, // BACK  // TOP LEFT VERT
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
                                    0.0, -1.0,  0.0};

                                              // COLOR (PER INSTANCE)
float CubeManager::instanceData[] = { 0.1,  0.8,  0.0, // 1
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

int CubeManager::vertexCount = 4 * 6;

CubeManager::CubeManager()
{
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenBuffers(1, &instanceBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(instanceData), instanceData,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    setShaderManager(new ShaderManager("../assets/shaders/"));
}

CubeManager::~CubeManager()
{
}

GLuint CubeManager::loadShader()
{
   return shaderManager->getProgram(2, "phongCube.vert", "phongCube.frag");
}

void CubeManager::draw(GLuint program)
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

    // Vertex Data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // TODO: Change this to be described by the ModelData struct
    glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), 0);
    glVertexAttribPointer(vertexNormalLoc, 3, GL_FLOAT, GL_TRUE,
        3 * sizeof(float), (void *)(vertexCount * 3 * sizeof(float)));

    // Instance data
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
    glVertexAttribPointer(vertexColorLoc, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), 0);
    glVertexAttribPointer(cubePosLoc, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void *)(6 * 3 * sizeof(float)));
    
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

bool CubeManager::insert(Cube& cube)
{
    return cubeMap.insert(
               make_pair(makeKey(cube.x, cube.y, cube.z), cube)).second;
}

void CubeManager::erase(int x, int y, int z)
{
    cubeMap.erase(makeKey(x, y, z));
}

void CubeManager::clear()
{
    cubeMap.clear();
}

Cube& CubeManager::at(int x, int y, int z)
{
    return cubeMap.at(makeKey(x,y,z));
}

void CubeManager::populateModelData()
{
    CubePosColor *instanceData = new CubePosColor[cubeMap.size()];

    // for each cube add position and color info
    int i = 0;
    for(map<MortonNumber, Cube>::iterator it = cubeMap.begin();
        it != cubeMap.end();
        it++, i++)
    {
        instanceData[i].position[0] = it->second.x;
        instanceData[i].position[1] = it->second.y;
        instanceData[i].position[2] = it->second.z;

        instanceData[i].color[0] = it->second.red;
        instanceData[i].color[1] = it->second.green;
        instanceData[i].color[2] = it->second.blue;
    }
    glGenBuffers(1, &instanceBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeMap.size() * sizeof(CubePosColor), vertexData,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete[] instanceData;
}

// Assumes we are fitting three 21 bit integers into a >63 bit type
// 2^21 = 2097152
MortonNumber CubeManager::makeKey(int x, int y, int z)
{
    return MortonNumber(x,y,z);
}
