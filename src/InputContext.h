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
    bool getMappedAction(Input::RawButton button, Input::Action& action) const;
    bool getMappedState(Input::RawButton button, Input::State& state) const;
    bool getMappedRange(Input::RawAxis axis, Input::Range& range) const;
protected:
private:
    std::map<Input::RawButton, Input::Action> actions;
    std::map<Input::RawButton, Input::State> states;
    std::map<Input::RawAxis, Input::Range> ranges;

    //std::map<Input::Range, float> sensitivities;
};

#endif
