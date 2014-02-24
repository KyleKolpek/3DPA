#include "Cube.h"
#include "CubeRenderer.h"
#include "CubeManager.h"
#include "Model.h"
#include "ModelBuilder.h"
#include "ShaderManager.h"

struct CubePosColor
{
    float position[3];
    float color[4];
};

CubeRenderer::CubeRenderer(ShaderManager *shaderManager):
    instanceBuffer(0),
    shaderManager(shaderManager)
{
    // Set up model for storing the cube data
    ModelBuilder mb;
    GLuint program = shaderManager->getProgram(2, "phongCube.vert",
                                                  "phongCube.frag");
    mb.setShaderProgram(program);
    mb.addVertexAttribute(glGetAttribLocation(program, "vertexPosition"),
                          3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0, 0);
    mb.addVertexAttribute(glGetAttribLocation(program, "vertexNormal"),
                          3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)(Cube::vertexCount * 3 * sizeof(float)), 0);
    mb.addVertexAttribute(glGetAttribLocation(program, "vertexColor"),
                          3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0, 1);
    mb.addVertexAttribute(glGetAttribLocation(program, "cubePosition"),
                          4, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                          (void *)(3 * sizeof(float)), 1);
    mb.setVertexCount(Cube::vertexCount);
    mb.setTextureCount(0);
    mb.setOwnershipType(OwnershipType::SELFISH);
    model = mb.getModel();

    model->bufferSubData(0, sizeof(Cube::vertexData), Cube::vertexData);
    //setShaderManager(new ShaderManager("../assets/shaders/"));
}
CubeRenderer::~CubeRenderer()
{
    delete model;
}

GLuint CubeManager::loadShader()
{
   return shaderManager->getProgram(2, "phongCube.vert", "phongCube.frag");
}

void CubeRenderer::populateModelData()
{
    const map<MortonNumber, Cube> &cubeMap = cubeManager.getCubeMap();

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
        instanceData[i].color[3] = it->second.alpha;
    }
    
    model->bufferSubData(sizeof(Cube::vertexData) + sizeof(CubePosColor),
                         cubeMap.size() * sizeof(CubePosColor), instanceData);
    delete[] instanceData;
}

// TODO: Update draw method
void CubeRenderer::draw(GLuint program)
{   
    if(cubeManager.wasUpdated)
    {
        populateModelData();
        cubeManager.wasUpdated = false;
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
        7 * sizeof(float), 0);
    glVertexAttribPointer(vertexColorLoc, 4, GL_FLOAT, GL_FALSE,
        7 * sizeof(float), (void *)( 3 * sizeof(float)));
    
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
