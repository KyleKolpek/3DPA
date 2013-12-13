#ifndef UPDATABLE_H
#define UPDATABLE_H

#include "InputMapper.h"

/***************************************************************************//**
 * Allows an object to be updated.
 * Provides a virtual void method, update(), to be run every frame.
 ******************************************************************************/
class Updatable
{
public:
    /***********************************************************************//**
     * Virtual destructor.
     **************************************************************************/
    virtual ~Updatable();

    /***********************************************************************//**
     * Handles input and updates the object.
     * \param[in] sec
     *     The number of seconds since the last update.
     **************************************************************************/
    //virtual void update(float sec) = 0;
    virtual void handleInput(InputMap &input) = 0;
};

#endif
