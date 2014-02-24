#ifndef CUBERENDERER_H
#define CUBERENDERER_H

class Model;
class ShaderManager;

class CubeRenderer: public Drawable
{
public:
    CubeRenderer();
    ~CubeRenderer();
    void draw();
    GLuint loadShader();
private:
    Model *model;
    CubeManager cubeManager;
    ShaderManager *shaderManager;
};

#endif
