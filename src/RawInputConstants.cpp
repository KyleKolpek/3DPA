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
    {SDLK_b, RAW_BUTTON_B},
    {SDLK_c, RAW_BUTTON_C},
    {SDLK_d, RAW_BUTTON_D},
    {SDLK_e, RAW_BUTTON_E},
    {SDLK_f, RAW_BUTTON_F},
    {SDLK_g, RAW_BUTTON_G},
    {SDLK_h, RAW_BUTTON_H},
    {SDLK_i, RAW_BUTTON_I},
    {SDLK_j, RAW_BUTTON_J},
    {SDLK_k, RAW_BUTTON_K},
    {SDLK_l, RAW_BUTTON_L},
    {SDLK_m, RAW_BUTTON_M},
    {SDLK_n, RAW_BUTTON_N},
    {SDLK_o, RAW_BUTTON_O},
    {SDLK_p, RAW_BUTTON_P},
    {SDLK_q, RAW_BUTTON_Q},
    {SDLK_r, RAW_BUTTON_R},
    {SDLK_s, RAW_BUTTON_S},
    {SDLK_t, RAW_BUTTON_T},
    {SDLK_u, RAW_BUTTON_U},
    {SDLK_v, RAW_BUTTON_V},
    {SDLK_w, RAW_BUTTON_W},
    {SDLK_x, RAW_BUTTON_X},
    {SDLK_y, RAW_BUTTON_Y},
    {SDLK_z, RAW_BUTTON_Z},
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
