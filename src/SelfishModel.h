#ifndef SELFISHMODEL_H
#define SELFISHMODEL_H

#include "Model.h"

/***************************************************************************//**
 * A subclass of Model that takes ownership of GPU model data.
 ******************************************************************************/
class SelfishModel: public Model
{
public:
    SelfishModel();
    virtual ~SelfishModel();
};

#endif
