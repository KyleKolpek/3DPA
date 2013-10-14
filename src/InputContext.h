#ifndef INPUTCONTEXT_H
#define INPUTCONTEXT_H

#include <map>
#include "InputConstants.h"
#include "RawInputConstants.h"

class InputContext
{
public:
    InputContext();
    ~InputContext();
    bool getMappedAction(RawButton button, Action& action) const;
    bool getMappedState(RawButton button, State& state) const;
    bool getMappedRange(RawAxis axis, Range& range) const;
protected:
private:
    std::map<Input::RawButton, Input::Action> actions;
    std::map<Input::RawButton, Input::State> states;
    std::map<Input::RawAxis, Input::Range> ranges;

    //std::map<Input::Range, float> sensitivities;
};

#endif
