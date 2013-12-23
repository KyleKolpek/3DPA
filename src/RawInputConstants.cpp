#include "RawInputConstants.h"
#include <map>
#include <cstdint>

using namespace Input;
static std::map<SDL_Keycode, RawButton> sdlKeyToRawMap = 
    {{SDLK_UP, RAW_BUTTON_UP},
    {SDLK_DOWN, RAW_BUTTON_DOWN},
    {SDLK_LEFT, RAW_BUTTON_LEFT},
    {SDLK_RIGHT, RAW_BUTTON_RIGHT},
    {SDLK_a, RAW_BUTTON_A},
    {SDLK_d, RAW_BUTTON_D},
    {SDLK_c, RAW_BUTTON_C},
    {SDLK_s, RAW_BUTTON_S},
    {SDLK_w, RAW_BUTTON_W},
    {SDLK_SPACE, RAW_BUTTON_SPACE},
    {SDLK_LSHIFT, RAW_BUTTON_LSHIFT},
    {SDLK_RSHIFT, RAW_BUTTON_RSHIFT},
    {SDLK_LALT, RAW_BUTTON_LALT},
    {SDLK_RALT, RAW_BUTTON_RALT},
    {SDLK_LCTRL, RAW_BUTTON_LCTRL},
    {SDLK_RCTRL, RAW_BUTTON_RCTRL}};

static std::map<uint8_t, RawButton> sdlButtonToRawMap = 
    {{SDL_BUTTON_LEFT,  RAW_BUTTON_LEFT_MOUSE},
    {SDL_BUTTON_MIDDLE, RAW_BUTTON_MIDDLE_MOUSE},
    {SDL_BUTTON_RIGHT,  RAW_BUTTON_RIGHT_MOUSE},
    {SDL_BUTTON_X1,     RAW_BUTTON_UNKNOWN},
    {SDL_BUTTON_X2,     RAW_BUTTON_UNKNOWN}};

// TODO: Change this to use a map if possible
RawButton Input::convertToRawButton(SDL_Event e)
{
    switch(e.type)
    {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            std::map<SDL_Keycode, RawButton>::iterator it =
                sdlKeyToRawMap.find(e.key.keysym.sym);
            if(it == sdlKeyToRawMap.end())
            {
                return RAW_BUTTON_UNKNOWN;
            }
            return it->second;
        }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            std::map<uint8_t, RawButton>::iterator it =
                sdlButtonToRawMap.find(e.button.button);
            if(it == sdlButtonToRawMap.end())
            {
                return RAW_BUTTON_UNKNOWN;
            }
            return it->second;
        }
        default:
            return RAW_BUTTON_UNKNOWN;
    }
}
