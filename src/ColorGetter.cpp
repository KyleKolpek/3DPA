#include <sstream>
#include <string>
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
    std::stringstream ss;
    ss << "rgb(" << (int)(red*255) << ","
                 << (int)(green*255) << ","
                 << (int)(blue*255) << ")";
    preview->SetProperty("background-color", ss.str().c_str());
}

void ColorGetter::setPreviewElement(Rocket::Core::Element *element)
{
    preview = element;
}
