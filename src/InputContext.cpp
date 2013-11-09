#include "InputContext.h"

using namespace Input;
using namespace std;

InputContext::InputContext():conversions(NULL)
{
    // Set up mappings here.
    // TODO: change this to take input from a file
    states[RAW_BUTTON_W] = STATE_CAMERA_MOVE_FORWARD;
    states[RAW_BUTTON_S] = STATE_CAMERA_MOVE_BACK;
    states[RAW_BUTTON_A] = STATE_CAMERA_MOVE_LEFT;
    states[RAW_BUTTON_D] = STATE_CAMERA_MOVE_RIGHT;
    states[RAW_BUTTON_SPACE] = STATE_CAMERA_MOVE_UP;
    states[RAW_BUTTON_C] = STATE_CAMERA_MOVE_DOWN;

    states[RAW_BUTTON_RIGHT_MOUSE] = STATE_CAMERA_ROTATE;

    actions[RAW_BUTTON_LEFT_MOUSE] = ACTION_ADD_CUBE;

    ranges[RAW_AXIS_MOUSE_X] = RANGE_ROTATE_CAMERA_X;
    ranges[RAW_AXIS_MOUSE_Y] = RANGE_ROTATE_CAMERA_Y;

    sensitivities[RANGE_ROTATE_CAMERA_X] = 1.5;
    sensitivities[RANGE_ROTATE_CAMERA_Y] = 1.5;
    conversions = new RangeConverter();
}

InputContext::~InputContext()
{
    delete conversions;
}

bool InputContext::getMappedAction(RawButton button, Action& action) const
{
    map<RawButton, Action>::const_iterator iter = actions.find(button);
    if(iter == actions.end())
    {
        return false;
    }

    action = iter->second;
    return true;
}

bool InputContext::getMappedState(RawButton button, State& state) const
{
    map<RawButton, State>::const_iterator iter = states.find(button);
    if(iter == states.end())
    {
        return false;
    }

    state = iter->second;
    return true;
}

bool InputContext::getMappedRange(RawAxis axis, Range& range) const
{
    map<RawAxis, Range>::const_iterator iter = ranges.find(axis);
    if(iter == ranges.end())
    {
        return false;
    }

    range = iter->second;
    return true;
}

double InputContext::getSensitivity(Input::Range range) const
{
    std::map<Input::Range, double>::const_iterator iter =
        sensitivities.find(range);
    if(iter == sensitivities.end())
    {
        return 1.0;
    }
    return iter->second;
}

const RangeConverter& InputContext::getConversions() const
{
    return *conversions;
}
