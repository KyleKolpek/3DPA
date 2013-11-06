#include "InputContext.h"

using namespace Input;
using namespace std;

InputContext::InputContext()
{
    // Set up mappings here.
    // TODO: change this to take input from a file
    states[SDLK_UP]    = STATE_CAMERA_MOVE_UP;
    states[SDLK_DOWN]  = STATE_CAMERA_MOVE_DOWN;
    states[SDLK_LEFT]  = STATE_CAMERA_MOVE_LEFT;
    states[SDLK_RIGHT] = STATE_CAMERA_MOVE_RIGHT;
}

InputContext::~InputContext()
{
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
