#ifndef RAWINPUTCONSTANTS_H
#define RAWINPUTCONSTANTS_H

#include <SDL_events.h>

namespace Input
{

enum RawButton
{
    RAW_BUTTON_UP              = 0x10000001,
    RAW_BUTTON_DOWN            = 0x10000002,
    RAW_BUTTON_LEFT            = 0x10000003,
    RAW_BUTTON_RIGHT           = 0x10000004,
    RAW_BUTTON_A               = 0x10000005,
    RAW_BUTTON_B               = 0x10000006,
    RAW_BUTTON_C               = 0x10000007,
    RAW_BUTTON_D               = 0x10000008,
    RAW_BUTTON_E               = 0x10000009,
    RAW_BUTTON_F               = 0x10000010,
    RAW_BUTTON_G               = 0x10000011,
    RAW_BUTTON_H               = 0x10000012,
    RAW_BUTTON_I               = 0x10000013,
    RAW_BUTTON_J               = 0x10000014,
    RAW_BUTTON_K               = 0x10000015,
    RAW_BUTTON_L               = 0x10000016,
    RAW_BUTTON_M               = 0x10000017,
    RAW_BUTTON_N               = 0x10000018,
    RAW_BUTTON_O               = 0x10000019,
    RAW_BUTTON_P               = 0x10000020,
    RAW_BUTTON_Q               = 0x10000021,
    RAW_BUTTON_R               = 0x10000022,
    RAW_BUTTON_S               = 0x10000023,
    RAW_BUTTON_T               = 0x10000024,
    RAW_BUTTON_U               = 0x10000025,
    RAW_BUTTON_V               = 0x10000026,
    RAW_BUTTON_W               = 0x10000027,
    RAW_BUTTON_X               = 0x10000028,
    RAW_BUTTON_Y               = 0x10000029,
    RAW_BUTTON_Z               = 0x10000030,
    RAW_BUTTON_SPACE           = 0x10000031,
    RAW_BUTTON_LEFT_MOUSE      = 0x10000032,
    RAW_BUTTON_RIGHT_MOUSE     = 0x10000033,
    RAW_BUTTON_MIDDLE_MOUSE    = 0x10000034,
    RAW_BUTTON_LSHIFT          = 0x10000035,
    RAW_BUTTON_RSHIFT          = 0x10000036,
    RAW_BUTTON_LALT            = 0x10000037,
    RAW_BUTTON_RALT            = 0x10000038,
    RAW_BUTTON_LCTRL           = 0x10000039,
    RAW_BUTTON_RCTRL           = 0x10000040,
}; 
enum RawAxis
{
    RAW_AXIS_MOUSE_X           = 0x20000001,
    RAW_AXIS_MOUSE_Y           = 0x20000002,
};

RawButton convertToRawButton(SDL_Event e);

}

#endif
