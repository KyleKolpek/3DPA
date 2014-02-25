#include "SelfishModel.h"


SelfishModel::SelfishModel():Model()
{
}

SelfishModel::~SelfishModel()
{
    for(GLuint i : modelData.textures)
    {
        glDeleteTextures(1, &i);
    }
    glDeleteBuffers(1, &modelData.vertexBuffer);
}
