#include <iostream>
#include <ctime>
#include <cstdlib>
#include "CubeGenerator.h"
#include "CubeManager.h"

using namespace std;

CubeGenerator::CubeGenerator():
    position(0.0, 0.0, 0.0),
    cubeManager(NULL)
{
    srand(time(NULL));
}

CubeGenerator::~CubeGenerator()
{
}

void CubeGenerator::moveTo(const glm::vec3 &position)
{
    this->position = position;
}

void CubeGenerator::addCube()
{
    Cube c;
    c.x = glm::floor(position.x);
    c.y = glm::floor(position.y);
    c.z = glm::ceil(position.z);

    c.red    = float(rand())/float(RAND_MAX);
    c.green  = float(rand())/float(RAND_MAX);
    c.blue   = float(rand())/float(RAND_MAX);
    c.alpha  = 1.0f;

    cubeManager->insert(c);
}

void CubeGenerator::removeCube()
{
    Cube c;
    c.x = glm::floor(position.x);
    c.y = glm::floor(position.y);
    c.z = glm::ceil(position.z);

    cubeManager->erase(c.x, c.y, c.z);
}

glm::vec3 CubeGenerator::getPosition()
{
    return position;
}

void CubeGenerator::setCubeManager(CubeManager *cubeManager)
{
    this->cubeManager = cubeManager;
}
