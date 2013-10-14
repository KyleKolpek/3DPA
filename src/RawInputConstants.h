#ifndef RAWINPUTCONSTANTS_H
#define RAWINPUTCONSTANTS_H

#include <SDL_keycode.h>

namespace Input
{

typedef SDL_Keycode RawButton;

enum RawAxis
{
    RAW_AXIS_MOUSE_X,
    RAW_AXIS_MOUSE_Y,
};

}

#endif
