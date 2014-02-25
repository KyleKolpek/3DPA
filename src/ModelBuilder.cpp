#include <algorithm>
#include "ModelBuilder.h"
#include "SOIL2/SOIL2.h"

ModelBuilder::ModelBuilder(std::string const &filename):
    vertexCount(0),
    vertexBuffer(NULL),
    textureCount(0),
    shaderProgram(0),
    vboManaged(false)
{
}

ModelBuilder::ModelBuilder()
{
}

ModelBuilder::~ModelBuilder()
{
}

void ModelBuilder::addVertexAttribute(GLuint index,
                                      GLint size,
                                      GLenum type,
                                      GLboolean normalized,
                                      GLsizei stride,
                                      GLvoid *pointer,
                                      GLuint divisor)
{
    VertexAttribute va;
    va.index = index;
    va.size = size;
    va.type = type;
    va.normalized = normalized;
    va.stride = stride;
    va.pointer = pointer;
    va.divisor = divisor;
    vertexAttribs.push_back(va);
}

void ModelBuilder::setVertexCount(GLsizei vertexCount)
{
    this->vertexCount = vertexCount;
}

void ModelBuilder::setTextureCount(GLsizei textureCount)
{
    this->textureCount = textureCount;
}

void ModelBuilder::addTexture(GLuint texture)
{
    textures.push_back(texture);
}

void ModelBuilder::addTexture(std::string const &filename)
{
    GLuint texture = SOIL_load_OGL_texture(filename.CString(),
                                           SOIL_LOAD_AUTO,
                                           SOIL_CREATE_NEW_ID,
                                           SOIL_FLAG_GL_MIPMAPS |
                                           SOIL_FLAG_NTSC_SAFE_RGB |
                                           SOIL_FLAG_COMPRESS_TO_DXT);
    textures.push_back(texture);
}

void ModelBuilder::bufferVertexData(GLsizeiptr size,
                                    GLvoid const *data,
                                    GLenum usage)
{
    if(!vboManaged)
    {
        glDeleteBuffers(1, &vertexBuffer);
    }
    glGenBuffers(1, &vertexBuffer);
    glBufferData(vertexBuffer, size, data, usage);
    vboManaged = false;
}

Model* ModelBuilder::getModel()
{
    Model *model;
    switch(ownershipType)
    {
        case OwnershipType.SELFISH:
            model = new SelfishModel();
            break;
        case OwnershipType.SELFLESS:
            model = new SelflessModel();
            break;
    }
    //model->modelData.textureCount  = this->textureCount;
    model->modelData.vertexBuffer  = this->vertexBuffer;
    model->modelData.vertexCount   = this->vertexCount;
    model->modelData.shaderProgram = this->shaderProgram;
    model->modelData.vertexAttribs = std::move(this->vertexAttribs);
    model->modelData.textures      = std::move(this->textures);
    vboManaged = true;
    clear();
    return model;
}

void ModelBuilder::clear()
{
    vertexCount = 0;
    vertexBuffer = NULL;
    shaderProgram = 0;
    textures.clear();
    vertexAttribs.clear();
    ownershipType = OwnershipType.SELFISH;
}
