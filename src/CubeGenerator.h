#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include "CubeManager.h"
#include "Drawable.h"
#include "Updatable.h"
#include "InputMapper.h"
#include "GLM/glm.hpp"

class CubeGenerator: public Drawable, public Updatable
{
public:

    CubeGenerator();

    void move(glm::vec3 delta);
    void moveTo(glm::vec3 position);
    void addCube();
    void removeCube();

    glm::vec3 getPosition();

    void draw(GLuint program);
    GLuint loadShader();

    CubeManager *cubeManager;
    void handleInput(InputMap &input);
private:
    struct CubePosColorAlpha
    {
        float position[3];
        float color[3];
        float alpha;
    };
    glm::vec3 position;
    Cube indicator;
    GLuint vertexBuffer;
    GLuint instanceBuffer;
};

#endif
