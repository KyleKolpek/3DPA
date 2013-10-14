#include "InputContext.h"

using namespace Input;
using namespace std;

InputContext::InputContext()
{
    // Set up mappings here.
    // TODO: change this to take input from a file
    ActionMap[RAW_BUTTON_W] = ACT_CAMERA_MOVE_UP;
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
