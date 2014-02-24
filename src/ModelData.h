#ifndef MODELDATA_H
#define MODELDATA_H

#include "stdgl.h"
#include <cstdint>
#include <vector>

struct VertexAttribute
{
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    GLuint divisor;
};

/***************************************************************************//**
 * Storage class for model data.
 * Holds raw data. To be filled by other tools for loading models from files or
 * other sources.
 * TODO: Store uniform descriptors?
 ******************************************************************************/
class ModelData
{
public:
    /***********************************************************************//**
     * Constructor.
     **************************************************************************/
    ModelData();

    /***********************************************************************//**gg
     * Destructor.
     **************************************************************************/
    ~ModelData();

    /***********************************************************************//**
     * Holds an array of VertexAttributes used to describe any attributes.
     **************************************************************************/
    std::vector<VertexAttribute> vertexAttribs;

    /***********************************************************************//**
     * Holds the vertex data for the model on the GPU.
     **************************************************************************/
    GLuint vertexBuffer;

    /***********************************************************************//**
     * Holds the number of vertices in the model.
     **************************************************************************/
    GLuint vertexCount;

    /***********************************************************************//**
     * Holds texture image information on the GPU.
     **************************************************************************/    
    std::vector<GLuint> textures;

    /***********************************************************************//**
     * Holds the ID of the compiled shader to be used.
     * NOTE: May be better off in Model, allowing different shaders per set of
     * data.
     **************************************************************************/
    GLuint shaderProgram;
};

#endif
