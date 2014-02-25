#include <cmath>
#include "Model.h"
#include "ModelData.h"
#include "GLM/glm.hpp"
#include "GLM/gtx/compatibility.hpp"

#define DEFAULT_BUFFER_SIZE 4

using namespace std;

Model::Model():
    position(0.0),
    scaleFactor(1.0),
    rotation(0.0),
    modelMatrix(1.0),
    vertexBufferSize(0),
    vertexDataSize(0),
    instanceCount(1)
{
}

Model::~Model()
{
}

glm::vec3 Model::getPosition()
{
    return position;
}

glm::mat4 const& Model::getModelMatrix()
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
    this->rotation += fmod(degrees, 360);
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

int Model::getVertexBufferSize()
{
    return vertexBufferSize;
}

int Model::getVertexDataSize()
{
    return vertexDataSize;
}

void Model::bufferData(GLintptr offset,
                       GLsizeiptr size,
                       const GLvoid * data)
{
    GLuint neededSize = offset + size;
    GLuint newSize = vertexBufferSize ? vertexBufferSize : DEFAULT_BUFFER_SIZE;

    // Automatically expand the vertex buffer as needed.
    while(newSize < neededSize)
    {
        newSize *= 2;
    }
    expandVertexBuffer(newSize);

    // Buffer the data.
    glBindBuffer(GL_ARRAY_BUFFER, modelData.vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::expandVertexBuffer(GLuint newSize)
{
    // Don't expand if we don't need to.
    if(vertexBufferSize >= newSize)
    {
        return;
    }
    GLuint newBuffer;
    vertexBufferSize = newSize;

    glGenBuffers(1, &newBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, newBuffer); // NOTE: Can one buffer be bound
                                              // to multiple targets?
                                              // Can I buffer only using
                                              // GL_COPY_WRITE_BUFFER?
    glBindBuffer(GL_COPY_READ_BUFFER, modelData.vertexBuffer);
    glBindBuffer(GL_COPY_WRITE_BUFFER, newBuffer);

    // TODO: Change GL_DYNAMIC_DRAW to a variable somewhere (ModelData?).
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, GL_DYNAMIC_DRAW);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0,
                        vertexDataSize);
    glDeleteBuffers(1, &modelData.vertexBuffer);

    modelData.vertexBuffer = newBuffer;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}
