#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "stdgl.h"
#include "ShaderManager.h"

/***************************************************************************//**
 * Allows an object to be drawn using OpenGL.
 * Provides two methods, draw() and setProgram(..), that are used to set up any
 * given Drawable object so that it can subsequently be drawn.
 ******************************************************************************/
class Drawable
{
public:
    /***********************************************************************//**
     * Virtual destructor.
     **************************************************************************/
    virtual ~Drawable();

    /***********************************************************************//**
     * Loads a shader using shaderManager.
     * \return
     *     A reference to the compiled shader program.
     **************************************************************************/
     virtual GLuint loadShader() = 0;

    /***********************************************************************//**
     * Draws the object.
     * Requires an OpenGL context to be initialized and draws using the shaders
     * contained in program.
     * \param[in] program
     *     The shader program to be used when drawing.
     **************************************************************************/
    virtual void draw(GLuint program) = 0;

    /***********************************************************************//**
     * Sets the shader manager to be used to create/retrieve programs.
     * Stores the shaderManager passed in as a parameter in the shaderManager
     * variable.
     * \param[in] shaderManager
     *     The ShaderManager to be stored.
     **************************************************************************/
    virtual void setShaderManager(ShaderManager *shaderManager);

protected:
    /***********************************************************************//**
     * Stores the ShaderManager that will be used to query programs.
     **************************************************************************/
     ShaderManager *shaderManager;
};

#endif
