#include "InputContext.h"
#include "Luatable/Value.h"
#include <iostream>

using namespace Input;
using namespace std;

InputContext::InputContext():conversions(NULL)
{
    // Set up mappings here.
    // TODO: change this to take input from a file
    Luatable::Value mainContext;
    if(!mainContext.loadFromFile("../assets/input/contexts/MainContext.lua"))
    {
        std::cerr << "Error opening input context files." << std::endl;
    }
    std::map<Luatable::Key, Luatable::Value>::iterator i;
    cout << hex;
    for(i = mainContext["states"].begin();
        i != mainContext["states"].end();
        i++)
    {
        states[static_cast<RawButton>(i->first.asInt())] =
            static_cast<State>(i->second.asInt());
    }
    for(i = mainContext["actions"].begin();
        i != mainContext["actions"].end();
        i++)
    {
        actions[static_cast<RawButton>(i->first.asInt())] =
            static_cast<Action>(i->second.asInt());
    }
    for(i = mainContext["ranges"].begin();
        i != mainContext["ranges"].end();
        i++)
    {
        ranges[static_cast<RawAxis>(i->first.asInt())] =
            static_cast<Range>(i->second.asInt());
    }
    
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
