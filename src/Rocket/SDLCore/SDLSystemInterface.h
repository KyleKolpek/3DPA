#ifndef SDLSYSTEMINTERFACE_H
#define SDLSYSTEMINTERFACE_H

#include <Rocket/Core/SystemInterface.h>

class SDLSystemInterface: public Rocket::Core::SystemInterface
{
public:
    float GetElapsedTime();
};

#endif
