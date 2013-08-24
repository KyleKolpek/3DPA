#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "stdgl.h"
#include "Drawable.h"
#include "GLM/glm.hpp"

class ModelData;

/***************************************************************************//**
 * A drawable class that can undergo most affine transformations.
 * This is one of the more basic drawable classes.
 ******************************************************************************/
class Model: public Drawable
{
public:
    Model(ModelData *modelData);
    virtual ~Model();

    // Inherited methods
    virtual void draw();

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
     * \param[in] fmodel
     *     The fmodel to multiply the scale by.
     **************************************************************************/
    void rotate(float degrees);

protected:
    /***********************************************************************//**
     * modelData stores OpenGL vertex pointers and attributes.
     **************************************************************************/
     ModelData *modelData;

    /***********************************************************************//**
     * The world position of the model.
     **************************************************************************/
    glm::vec3 position;

    /***********************************************************************//**
     * The amount to scale the model.
     **************************************************************************/
    float scaleFactor;

    /***********************************************************************//**
     * The rotation of the model.
     **************************************************************************/    
    float rotation;

    /***********************************************************************//**
     * The model matrix, used for transformations and other operations.
     **************************************************************************/
    glm::mat4 modelMatrix;

    /***********************************************************************//**
     * Creates the model's model view matrix. This enables us to avoid repeat 
     * calculations.
     **************************************************************************/
    void createModelMatrix();

};

#endif
