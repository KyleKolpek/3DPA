#include <SDL.h>
#include <Rocket/SDLCore/SDLSystemInterface.h>

float SDLSystemInterface::GetElapsedTime()
{
    return static_cast<float>(SDL_GetTicks())/1000.0;
}
