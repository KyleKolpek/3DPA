#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include <string>
#include "stdgl.h"
#include "ModelData.h"

enum class OwnershipType
{
    SELFISH,
    SELFLESS
};

class ModelBuilder
{
public:
    /***********************************************************************//**
     * Constructor used for filling model data from a file definition.
     * \param[in] filename
     *     The name of the file to be loaded.
     **************************************************************************/
    ModelBuilder(std::string filename);
    ModelBuilder();
    ~ModelBuilder();

    /***********************************************************************//**
     * Adds an attribute to the array of VertexAttributes in the model data.
     * \param[in] index
     *     The cooresponding attribute index in the shader program.
     * \param[in] size
     *     The number of values of type 'type' representing the vertex
     *     attribute.
     * \param[in] type
     *     The type of the vertex attribute.
     * \param[in] normalized
     *     Whether the vertex attribute should be normalized when passed to the
     *     shader.
     * \param[in] stride
     *     The distance in bytes between the start of subsequent vertices.
     * \param[in] divisor
     *     The number of instances to be passed between updates of the
    *      attribute.
     **************************************************************************/
    void addVertexAttribute(GLuint index,
                            GLint size,
                            GLenum type,
                            GLboolean normalized,
                            GLsizei stride,
                            GLuint divisor);
    
    /***********************************************************************//**
     * Sets what shader program the model should be rendered with.
     * \param[in] program
     *     The compiled shader the model should be rendered with.
     **************************************************************************/
     void setShaderProgram(GLuint program);

    /***********************************************************************//**
     * Sets the number of vertices stored by this model.
     * \param[in] vertexCount
     *     The number of vertices stored in the model.
     **************************************************************************/
    void setVertexCount(GLsizei vertexCount);

    /***********************************************************************//**
     * Adds a texture ID to the array of textures stored by this model.
     * \param[in] texture
     *     The ID of a texture to be added to the model.
     **************************************************************************/
    void addTexture(GLuint texture);

    /***********************************************************************//**
     * Loads a texture and adds a texture ID to the array of textures stored by
     * this model.
     * \param[in] filename
     *     The name of a texture file to be loaded and added to the model.
     **************************************************************************/
    void addTexture(std::string const &filename);

    /***********************************************************************//**
     * Buffers the vertex data onto the GPU.
     * This is a simple wrapper around glBufferData. Be careful using this
     * builder because it allows multiple Models to refer to the same buffer,
     * potentially leading to premature deletion.
     * \param[in] size
     *     The size in bytes of the data to be buffered.
     * \param[in] data
     *     A pointer to the data to be copied to the buffer.
     * \param[in] usage
     *     A description of how the data is expected to be used. It defaults to
     *     GL_STATIC_DRAW.
     **************************************************************************/
    void bufferVertexData(GLsizeiptr size,
                          GLvoid const *data,
                          GLenum usage=GL_STATIC_DRAW);

    /***********************************************************************//**
     * Sets the ownership behavior of the model.
     * \param[in] type
     *     Describes the ownership of the model.
     **************************************************************************/
     void setOwnershipType(OwnershipType type);

    /***********************************************************************//**
     * Returns a model built using the internal state, then clears the state.
     **************************************************************************/
     Model* getModel();

private:
    GLsizei vertexCount;
    GLuint vertexBuffer;
    GLuint shaderProgram;
    std::vector<GLuint> textures;
    std::vector<VertexAttribute> vertexAttribs;
    OwnershipType ownershipType;
    bool vboManaged;

    /***********************************************************************//**
     * Clears the state contained in the ModelBuilder.
     **************************************************************************/
     void clear();
};

#endif
