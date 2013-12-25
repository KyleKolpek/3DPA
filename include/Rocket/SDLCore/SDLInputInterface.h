#ifndef SDLINPUTINTERFACE_H
#define SDLINPUTINTERFACE_H

#include <map>
#include "SDL2/SDL.h"
#include "Rocket/Core.h"

class SDLInputInterface
{
public:
    SDLInputInterface(Rocket::Core::Context * const context);
    ~SDLInputInterface();
    void handleRocketInput(SDL_Event event);

private:
    int generateRocketModifiers(SDL_Event &event);

    Rocket::Core::Context *context;
    static std::map<SDL_Scancode, Rocket::Core::Input::KeyIdentifier> keymap;
};

#endif
