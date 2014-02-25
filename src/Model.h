#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "stdgl.h"
#include "GLM/glm.hpp"

class ModelData;

/***************************************************************************//**
 * A drawable class that can undergo most affine transformations.
 ******************************************************************************/
class Model
{
public:
    Model();
    virtual ~Model() = 0;

    /***********************************************************************//**
     * Retrieve the model's position in world space.
     * \return  
     *     The model's position in world space.
     **************************************************************************/
    glm::vec3 getPosition();

    /***********************************************************************//**
     * Retrieve a const reference to the model matrix
     * \return  
     *     The model matrix.
     **************************************************************************/
    glm::vec4 const& getModelMatrix();

    /***********************************************************************//**
     * Sets the model's position in world/dungeon space.
     * (0,0) is the top left point of the dungeon.
     * \param[in] position
     *     A position that will be assigned to the position member and used to
     *     translate the model.
     **************************************************************************/
    void setPosition(glm::vec3 const &position);

    /***********************************************************************//**
     * Sets the model's scale and modifies the radius accordingly.
     * \param[in] scale
     *     The scale of the model to be used.
     **************************************************************************/
    void setScale(float scale);

    /***********************************************************************//**
     * Sets the model's rotation in degrees.
     * \param[in] degrees
     *     The number of degrees to rotate the model counter-clockwise.
     **************************************************************************/
    void setRotation(float degrees);

    /***********************************************************************//**
     * Moves the model position by delta.
     * \param[in] delta
     *     The amount to translate the position by.
     **************************************************************************/
    void move(glm::vec3 const &delta);
    
    /***********************************************************************//**
     * Scales the model scale by a fmodel.
     * \param[in] fmodel
     *     The fmodel to multiply the scale by.
     **************************************************************************/
    void scale(float fmodel);

    /***********************************************************************//**
     * Scales the model by a fmodel.
     * TODO: Expand to quaternion rotation or something.
     * \param[in] degrees
     *     The number of degrees to rotate by around the Y axis.
     **************************************************************************/
    void rotate(float degrees);

    /***********************************************************************//**
     * Returns the current size of the data stored in the vertex buffer in
     * bytes.
     **************************************************************************/
    int getVertexDataSize();

    /***********************************************************************//**
     * Returns the current size of the vertex buffer in bytes.
     **************************************************************************/
    int getVertexBufferSize();

    /***********************************************************************//**
     * The OpenGL vertex pointers and attributes.
     **************************************************************************/
    ModelData modelData;

    /***********************************************************************//**
     * Allows for substituting buffer data into the model's vertex buffer. This
     * method allows for automatic growth of the vertex buffer.
     * \param[in] offset
     *     The offset into the buffer where the data substitution will begin.
     * \param[in] size
     *     The size in bytes of the data to be replaced.
     * \param[in] data
     *     A pointer to the dat to be substituted into the vertex buffer.
     **************************************************************************/
    void bufferData(GLintptr offset, GLsizeiptr size, const GLvoid * data);

    /***********************************************************************//**
     * Holds the number of instances to be drawn.
     **************************************************************************/
    GLuint instanceCount;
private:
    /***********************************************************************//**
     * Expands the size of the vertex buffer to newSize, maintaining all data.
     * \param[in] newSize
     *     The new size of the vertex buffer.
     **************************************************************************/
    void expandVertexBuffer(GLuint newSize);

    /***********************************************************************//**
     * Creates the model's model view matrix. This enables us to avoid repeat 
     * calculations.
     **************************************************************************/
    void createModelMatrix();

    /***********************************************************************//**
     * The world position of the model.
     **************************************************************************/
    glm::vec3 position;

    /***********************************************************************//**
     * The amount to scale the model.
     **************************************************************************/
    float scaleFactor;

    /***********************************************************************//**
     * The rotation of the model in degrees.
     * TODO: Expand to quaternion rotation or something.
     **************************************************************************/    
    float rotation;

    /***********************************************************************//**
     * The model matrix, used for transformations and other operations.
     **************************************************************************/
    glm::mat4 modelMatrix;

    /***********************************************************************//**
     * Stores the number of bytes currently stored in the vertex buffer.
     **************************************************************************/
    GLuint vertexDataSize;

    /***********************************************************************//**
     * Stores the size of the buffer currently allocated on the GPU.
     **************************************************************************/
    GLuint vertexBufferSize;
};

#endif
