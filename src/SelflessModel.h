#ifndef SELFLESSMODEL_H
#define SELFLESSMODEL_H

#include "Model.h"

/***************************************************************************//**
 * A subclass of Model that leaves management of GPU model data to the user.
 ******************************************************************************/
class SelflessModel: public Model
{
public:
    SelflessModel();
    virtual ~SelflessModel();
};

#endif
