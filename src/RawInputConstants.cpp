#include "RawInputConstants.h"

using namespace Input;

// TODO: Change this to use a map if possible
RawButton Input::convertToRawButton(SDL_Event e)
{
    switch(e.type)
    {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            switch(e.key.keysym.sym)
            {
                case SDLK_UP:
                    return RAW_BUTTON_UP;
                case SDLK_DOWN:
                    return RAW_BUTTON_DOWN;
                case SDLK_LEFT:
                    return RAW_BUTTON_LEFT;
                case SDLK_RIGHT:
                    return RAW_BUTTON_RIGHT;
                case SDLK_a:
                    return RAW_BUTTON_A;
                case SDLK_d:
                    return RAW_BUTTON_D;
                case SDLK_c:
                    return RAW_BUTTON_C;
                case SDLK_s:
                    return RAW_BUTTON_S;
                case SDLK_w:
                    return RAW_BUTTON_W;
                case SDLK_SPACE:
                    return RAW_BUTTON_SPACE;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            switch(e.button.button)
            {
                case SDL_BUTTON_LEFT:
                    return RAW_BUTTON_LEFT_MOUSE;
                case SDL_BUTTON_RIGHT:
                    return RAW_BUTTON_RIGHT_MOUSE;
                case SDL_BUTTON_MIDDLE:
                    return RAW_BUTTON_MIDDLE_MOUSE;
            }
            break;
    }
}
