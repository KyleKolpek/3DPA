#include "Cube.h"
#include "CubeModeler.h"
#include "CubeManager.h"
#include "ShaderManager.h"

struct CubePosColor
{
    float position[3];
    float color[4];
};

CubeModeler::CubeModeler(ShaderManager &shaderManager):
    SelfishModel(),
    instanceBuffer(0)
{
    // NOTE: Uses c++11 initialization lists, possibly incorrectly
    modelData->shaderProgram = shaderManager.getProgram(2, "phongCube.vert",
                                                           "phongCube.frag");
    modelData->vertexAttribs.push_back(
                         {glGetAttribLocation(program, "vertexPosition"),
                          3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0, 0});
    modelData->vertexAttribs.push_back(
                         {glGetAttribLocation(program, "vertexNormal"),
                          3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)(Cube::vertexCount * 3 * sizeof(float)), 0});
    modelData->vertexAttribs.push_back(
                         {glGetAttribLocation(program, "vertexColor"),
                          3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0, 1});
    modelData->vertexAttribs.push_back(
                         {glGetAttribLocation(program, "cubePosition"),
                          4, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                          (void *)(3 * sizeof(float)), 1});
    modelData->vertexCount = Cube::vertexCount;
    instanceCount = 1;
    bufferData(0, sizeof(Cube::vertexData), Cube::vertexData);

    CubePosColor c = {{0.0, 0.0, 0.0},
                      {1.0, 1.0, 1.0, .25}};
    model->bufferData(sizeof(Cube::vertexData),sizeof(CubePosColor), &c);

    cubeGenerator.setCubeManager(&cubeManager);
}

CubeModeler::~CubeModeler()
{
}

void CubeModeler::populateModelData()
{
    const map<MortonNumber, Cube> &cubeMap = cubeManager.getCubeMap();

    CubePosColor *instanceData = new CubePosColor[cubeMap.size()];

    // for each cube add position and color info
    int i = 0;
    for(map<MortonNumber, Cube>::const_iterator it = cubeMap.cbegin();
        it != cubeMap.cend();
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
    
    model->bufferData(sizeof(Cube::vertexData) + sizeof(CubePosColor),
                      cubeMap.size() * sizeof(CubePosColor), instanceData);
    delete[] instanceData;
}

void CubeModeler::handleInput(InputMap &input)
{
    if(input.actions.find(Input::ACTION_ADD_CUBE) != input.actions.end())
    {
        if(input.states.find(Input::STATE_SHIFT_DOWN) != input.states.end())
        {
            cubeGenerator.removeCube();
            instanceCount = cubeMap.size() + 1; // +1 for the indicator instance
        }
        else
        {
            cubeGenerator.addCube();
            instanceCount = cubeMap.size() + 1;
        }
    }
}

void CubeModeler::setActiveCubePos(const glm::vec3 &position)
{
    cubeGenerator.moveTo(position);
    CubePosColor c = {{glm::floor(position.x),
                       glm::floor(position.y),
                       glm::ceil(position.z)},
                      {1.0, 1.0, 1.0, .25}};
    model->bufferData(sizeof(Cube::vertexData),sizeof(CubePosColor), &c);
}
