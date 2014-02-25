#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include "GLM/glm.hpp"
#include "Cube.h"

class CubeManager;

class CubeGenerator
{
public:

    CubeGenerator();
    ~CubeGenerator();

    void moveTo(const glm::vec3 &position);
    void addCube();
    void removeCube();
    void setCubeManager(CubeManager *cubeManager);

    glm::vec3 getPosition();
private:
    glm::vec3 position;
    Cube indicator;
    CubeManager *cubeManager;
};

#endif
