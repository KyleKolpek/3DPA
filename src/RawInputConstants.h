#ifndef RAWINPUTCONSTANTS_H
#define RAWINPUTCONSTANTS_H

#include <SDL_events.h>

namespace Input
{

enum RawButton
{
    RAW_BUTTON_UP,
    RAW_BUTTON_DOWN,
    RAW_BUTTON_LEFT,
    RAW_BUTTON_RIGHT,
    RAW_BUTTON_A,
    RAW_BUTTON_C,
    RAW_BUTTON_D,
    RAW_BUTTON_S,
    RAW_BUTTON_W,
    RAW_BUTTON_SPACE,
    RAW_BUTTON_LEFT_MOUSE,
    RAW_BUTTON_RIGHT_MOUSE,
    RAW_BUTTON_MIDDLE_MOUSE,
}; 
enum RawAxis
{
    RAW_AXIS_MOUSE_X,
    RAW_AXIS_MOUSE_Y,
};

RawButton convertToRawButton(SDL_Event e);

}

#endif
