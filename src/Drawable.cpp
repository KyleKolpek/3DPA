#include "Drawable.h"

Drawable::~Drawable()
{
}

void Drawable::setShaderManager(ShaderManager *shaderManager)
{
    this->shaderManager = shaderManager;
}
