#include <cmath>
#include "SOIL/SOIL.h"
#include "Model.h"
#include "ModelData.h"
#include "GLM/glm.hpp"
#include "GLM/gtx/compatibility.hpp"

using namespace std;

Model::Model(ModelData *modelData):
    position(0.0),
    scaleFactor(1.0),
    rotation(0.0),
    radius(0.5),
    vertexCount(0),
    vertexBuffer(NULL),
    texture(NULL),
    modelMatrix(1.0),
    modelData(modelData)
{
}

Model::~Model()
{
    delete modelData;
}

void Model::draw()
{
    
/*
    // Store a ShaderManager over a program
    GLuint program = shaderManager->getProgram(2, "phongTex.vert",
        "phongTexPtLights.frag");
    glUseProgram(program);

    GLint mvLoc   = glGetUniformLocation(program, "modelView");
    GLint nmvLoc  = glGetUniformLocation(program, "normalModelView");
    GLint projLoc = glGetUniformLocation(program, "projection");
    GLint texLoc  = glGetUniformLocation(program, "texture");

    glm::mat4 MV   = camera->getViewMatrix() * modelMatrix;
    glm::mat4 proj = camera->getProjectionMatrix();

    // TODO: Error check here.
    if(mvLoc != -1)
    {
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &MV[0][0]);
    }
    else
    {
        cerr << "Error: Cannot find modelView location" << endl;
        return;
    }

    if(nmvLoc != -1)
    {
        glUniformMatrix4fv(nmvLoc, 1, GL_FALSE,
            &glm::transpose(glm::inverse(MV))[0][0]);
    }
    else
    {
        cerr << "Error: Cannot find normalModelView location" << endl;
        return;
    }
    
    if(projLoc != -1)
    {
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
    }
    else
    {
        cerr << "Error: Cannot find projection location" << endl;
        return;
    }

    if(texLoc != -1)
    {
        glUniform1i(texLoc, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, modelData->textures[0]);
    }
    else
    {
        cerr << "Error: Cannot find texture location" << endl;
        return;
    }

    GLuint vertexPosLoc = glGetAttribLocation(program, "vertexPosition");
    GLuint vertexNormalLoc = glGetAttribLocation(program, "vertexNormal");
    GLuint vertexTexCoordLoc = glGetAttribLocation(program, "vertexTexCoord");

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
    if(vertexTexCoordLoc == -1)
    {
        cerr << "Error: Cannot find vertexTexCoord location" << endl;
        return;
    }

    glEnableVertexAttribArray(vertexPosLoc);
    glEnableVertexAttribArray(vertexNormalLoc);
    glEnableVertexAttribArray(vertexTexCoordLoc);

    glBindBuffer(GL_ARRAY_BUFFER, modelData->vertexBuffer);
    // TODO: Change this to be described by the ModelData struct
    glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), 0);
    glVertexAttribPointer(vertexNormalLoc, 3, GL_FLOAT, GL_TRUE,
        8 * sizeof(float), (void *)(3 * sizeof(float)));
    glVertexAttribPointer(vertexTexCoordLoc, 2, GL_FLOAT, GL_TRUE,
        8 * sizeof(float), (void *)(6 * sizeof(float)));

    // TODO: Change GL_TRIANGLES to account for modelData->vertexType
    glDrawArrays(GL_TRIANGLES, 0, modelData->vertexCount);
    glDisableVertexAttribArray(vertexPosLoc);
    glDisableVertexAttribArray(vertexNormalLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);*/
}

glm::vec3 Model::getPosition()
{
    return position;
}

glm::vec4 const& getModelMatrix()
{
    return modelMatrix;
}

void Model::setPosition(glm::vec3 const &position)
{
    this->position = position;
    createModelMatrix();
}

void Model::setScale(float scale)
{
    this->scaleFactor = scale;
    this->radius = 0.5 * scale; //TODO: fix magic numbers
    createModelMatrix();
}

void Model::setRotation(float degrees)
{
    this->rotation = degrees;
    createModelMatrix();
}

void Model::move(glm::vec3 const &delta)
{
    position += delta;

    // Calculate the direction the model should face
    /*
    float theta = glm::degrees(glm::atan2(-delta.x, delta.z));
    setRotation(theta);
    */
    createModelMatrix();
}

void Model::scale(float factor)
{
    this->scaleFactor *= factor;
    createModelMatrix();
}

void Model::rotate(float degrees)
{
    this->rotation += degrees;
    createModelMatrix();
}

void Model::createModelMatrix()
{
    float theta = glm::radians(rotation);
    glm::mat4 translationMat(1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0,
                             position.x, position.y, position.z, 1.0);
    glm::mat4 scaleMat(scaleFactor, 0.0, 0.0, 0.0,
                       0.0, scaleFactor, 0.0, 0.0,
                       0.0, 0.0, scaleFactor, 0.0,
                       0.0, 0.0, 0.0, 1.0);
    glm::mat4 rotateMat(glm::cos(theta), 0.0, glm::sin(theta), 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        -glm::sin(theta), 0.0, glm::cos(theta), 0.0,
                        0.0, 0.0, 0.0, 1.0);
    modelMatrix = translationMat * scaleMat * rotateMat;
}
