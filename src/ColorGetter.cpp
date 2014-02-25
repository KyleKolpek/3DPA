#include <iostream>
#include "ColorGetter.h"

ColorGetter::ColorGetter():
    red(0.0),
    green(0.0),
    blue(0.0)
{
}

ColorGetter::~ColorGetter()
{
}

float ColorGetter::getRed()
{
    return red;
}

float ColorGetter::getGreen()
{
    return green;
}

float ColorGetter::getBlue()
{
    return blue;
}

void ColorGetter::ProcessEvent(Rocket::Core::Event& event)
{
    if(event.GetCurrentElement()->GetId() == "red")
    {
        red = event.GetParameter<float>("value", 0.0);
    }
    if(event.GetCurrentElement()->GetId() == "green")
    {
        green = event.GetParameter<float>("value", 0.0);
    }
    if(event.GetCurrentElement()->GetId() == "blue")
    {
        blue = event.GetParameter<float>("value", 0.0);
    }
}
