#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include "GLM/glm.hpp"
#include "Cube.h"
#include "ColorGetter.h"

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
    
    void attachListener(Rocket::Core::Element *element);

    glm::vec3 getPosition();
private:
    glm::vec3 position;
    ColorGetter colorGetter;
    Cube indicator;
    CubeManager *cubeManager;
};

#endif
