#ifndef CUBEMODELER_H
#define CUBEMODELER_H

#include "Updatable.h"
#include "SelfishModel.h"
#include "ShaderManager.h"
#include "CubeManager.h"
#include "CubeGenerator.h"
#include "GLM/glm.hpp"

class CubeModeler: public SelfishModel, public Updatable
{
public:
    CubeModeler(ShaderManager &shaderManager);
    ~CubeModeler();

    void handleInput(InputMap &input);
    void setActiveCubePos(const glm::vec3 &position);
private:
    CubeManager cubeManager;
    CubeGenerator cubeGenerator;
    void populateModelData();
};

#endif