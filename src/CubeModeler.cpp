#include <map>
#include "Cube.h"
#include "CubeModeler.h"
#include "CubeManager.h"
#include "ShaderManager.h"

using namespace std;

struct CubePosColor
{
    float position[3];
    float color[4];
};

CubeModeler::CubeModeler(ShaderManager &shaderManager,
                         Rocket::Core::Element *element):
    SelfishModel()
{
    // NOTE: Uses c++11 initialization lists, possibly incorrectly
    GLuint program = shaderManager.getProgram(2, "phongCube.vert",
                                                 "phongCube.frag");
    modelData.shaderProgram = program;
    modelData.vertexAttribs.push_back(
                        {glGetAttribLocation(program, "vertexPosition"),
                         3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0, 0});
    modelData.vertexAttribs.push_back(
                        {glGetAttribLocation(program, "vertexNormal"),
                         3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                         (void *)(Cube::vertexCount * 3 * sizeof(float)), 0});
    modelData.vertexAttribs.push_back(
                        {glGetAttribLocation(program, "cubePosition"),
                         3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                         (void *)(Cube::vertexDataSize), 1});
    modelData.vertexAttribs.push_back(
                        {glGetAttribLocation(program, "vertexColor"),
                         4, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                         (void *)(Cube::vertexDataSize + 3 * sizeof(float)),
                         1});
    modelData.vertexCount = Cube::vertexCount;
    instanceCount = 1;
    bufferData(0, Cube::vertexDataSize, Cube::vertexData);

    CubePosColor c = {{0.0, 0.0, 0.0},
                      {1.0, 1.0, 1.0, .25}};
    bufferData(Cube::vertexDataSize, sizeof(CubePosColor), &c);

    cubeGenerator.setCubeManager(&cubeManager);
    cubeGenerator.attachListener(element);
}

CubeModeler::~CubeModeler()
{
}

void CubeModeler::populateModelData()
{
    const map<MortonNumber, Cube> &cubeMap = cubeManager.getCubeMap();

    CubePosColor *instanceData = new CubePosColor[cubeMap.size() + 1];

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

    // Crap to make the highlight draw last.
    // It would be easier to move this back to the start of the instance data
    // and not worry about it here, but our transparency wouldn't work then.
    instanceData[cubeMap.size()].position[0] = cubeGenerator.getPosition().x;
    instanceData[cubeMap.size()].position[1] = cubeGenerator.getPosition().y;
    instanceData[cubeMap.size()].position[2] = cubeGenerator.getPosition().z;

    instanceData[i].color[0] = 1.0;
    instanceData[i].color[1] = 1.0;
    instanceData[i].color[2] = 1.0;
    instanceData[i].color[3] = 0.25;
    
    bufferData(Cube::vertexDataSize, (cubeMap.size() + 1) * sizeof(CubePosColor),
    instanceData);
    delete[] instanceData;
}

void CubeModeler::handleInput(InputMap &input)
{
    if(input.actions.find(Input::ACTION_ADD_CUBE) != input.actions.end())
    {
        if(input.states.find(Input::STATE_SHIFT_DOWN) != input.states.end())
        {
            cubeGenerator.removeCube();
            // +1 for the indicator instance
            instanceCount = cubeManager.getCubeMap().size() + 1;
            populateModelData();
        }
        else
        {
            cubeGenerator.addCube();
            instanceCount = cubeManager.getCubeMap().size() + 1;
            populateModelData();
        }
    }
}

void CubeModeler::setActiveCubePos(const glm::vec3 &position)
{
    cubeGenerator.moveTo(position);
    CubePosColor c = {{glm::floor(position.x),
                       glm::floor(position.y),
                       glm::ceil(position.z)},
                      {1.0, 1.0, 1.0, 0.25}};
    bufferData(Cube::vertexDataSize +
               cubeManager.getCubeMap().size() * sizeof(CubePosColor),
               sizeof(CubePosColor), &c);
}
