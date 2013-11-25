#include "CubeManager.h"
#include "Model.h"
#include "ModelData.h"
#include <iostream>

using namespace std;

CubeManager::CubeManager():
    needsUpdated(false),
    instanceBuffer(0)
{
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Cube::vertexCount * 3 * 2,
        Cube::vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //setShaderManager(new ShaderManager("../assets/shaders/"));
}

CubeManager::~CubeManager()
{
    glDeleteBuffers(1, &vertexBuffer);
}

GLuint CubeManager::loadShader()
{
   return shaderManager->getProgram(2, "phongCube.vert", "phongCube.frag");
}

void CubeManager::draw(GLuint program)
{   
    if(needsUpdated)
    {
        populateModelData();
        needsUpdated = false;
    }

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
        6 * sizeof(float), 0);
    glVertexAttribPointer(vertexColorLoc, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(float), (void *)( 3 * sizeof(float)));
    
    glVertexAttribDivisor(cubePosLoc, 1);
    glVertexAttribDivisor(vertexColorLoc, 1);

    // TODO: Change GL_TRIANGLES to account for modelData->vertexType
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, Cube::vertexCount,
        cubeMap.size());

    glVertexAttribDivisor(cubePosLoc, 0);
    glVertexAttribDivisor(vertexColorLoc,0);
    glDisableVertexAttribArray(vertexPosLoc);
    glDisableVertexAttribArray(vertexNormalLoc);
    glDisableVertexAttribArray(cubePosLoc);
    glDisableVertexAttribArray(vertexColorLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool CubeManager::insert(const Cube& cube)
{
    needsUpdated = true;
    return cubeMap.insert(
               make_pair(makeKey(cube.x, cube.y, cube.z), cube)).second;
}

void CubeManager::erase(int x, int y, int z)
{
    needsUpdated = true;
    cubeMap.erase(makeKey(x, y, z));
}

void CubeManager::clear()
{
    needsUpdated = true;
    cubeMap.clear();
}

Cube& CubeManager::at(int x, int y, int z)
{
    return cubeMap.at(makeKey(x,y,z));
}

void CubeManager::populateModelData()
{
    // Delete the stale buffer
    glDeleteBuffers(1, &instanceBuffer);

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
    glBufferData(GL_ARRAY_BUFFER, cubeMap.size() * sizeof(CubePosColor),
                 instanceData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete[] instanceData;
}

// Assumes we are fitting three 21 bit integers into a >63 bit type
// 2^21 = 2097152
MortonNumber CubeManager::makeKey(int x, int y, int z)
{
    return MortonNumber(x,y,z);
}
