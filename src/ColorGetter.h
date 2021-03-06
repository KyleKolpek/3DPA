#ifndef COLORGETTER_H
#define COLORGETTER_H

#include "Rocket/Core.h"

class ColorGetter: public Rocket::Core::EventListener
{
public:
    ColorGetter();
    ~ColorGetter();
    virtual void ProcessEvent(Rocket::Core::Event& event);
    void setPreviewElement(Rocket::Core::Element *element);
    float getRed();
    float getGreen();
    float getBlue();
private:
    float red;
    float green;
    float blue;
    Rocket::Core::Element *preview;
};

#endif
