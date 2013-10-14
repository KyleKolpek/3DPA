#include <exception>
#include "InputMapper.h"
#include "InputContext.h"

using namespace std;

void InputMap::removeAction(Action action)
{
    actions.erase(action);
}

void InputMap::removeState(State state)
{
    states.erase(state);
}

void InputMap::removeRange(Range range)
{
    ranges.erase(range);
}

InputMapper::InputMapper()
{
    inputContexts["test"] = new InputContext();
}

InputMapper::~InputMapper()
{
    for(map<string, InputContext*>::iterator i = inputContexts.begin();
        i != inputContexts.end(); i++)
    {
        delete i->second;
    }
}

void InputMapper::pushContext(const string& contextName)
{
    map<string, InputContext*>::const_iterator i =
        inputContexts.find(contextName);
    if(i == inputContexts.end())
    {
        throw exception("Invalid InputContext pushed.");
    }
    activeContexts.push_front(i->second);
}

void InputMapper::popContext()
{
    if(activeContexts.empty())
    {
        throw exception("No active InputContexts available to pop.");
    }
    activeContexts.pop_front();
}

void InputMapper::addCallback(InputCallback callback, int priority)
{
    callbacks.insert(pair<int, InputCallback>(priority, callback));
}

void InputMapper::processButtonInput(RawButton button,
                                     bool pressed,
                                     bool previouslyPressed)
{
    Action action;
    State state;

    // Action
    if(pressed && !previouslyPressed)
    {
        if(getActionFromContext(button, action))
        {
            currentInput.actions.insert(action);
            return;
        }
    }

    if(pressed)
    {
        if(getStateFromContext(button, state))
        {
            currentInput.states.insert(state);
            return;
        }
    }

    clearInputPerButton(button);
}

void InputMapper::processAxisInput(RawAxis axis, float value)
{
    for(list<InputContext*>::const_iterator i = activeContexts.begin();
        i != activeContexts.end(); i++)
    {
        const InputContext* context = *i;
        Range range;
        if(context->getMappedRange(axis, range))
        {
            //currentInput.ranges[range] = context;
            break;
        }
    }
}

bool InputMapper::getActionFromActiveContexts(RawButton button,
                                              Action& action) const
{
    for(list<InputContext*>::const_iterator i = activeContexts.begin();
        i != activeContexts.end(); i++)
    {
        const InputContext* context = *i;
        if(context->getMappedAction(button, action))
        {
            return true;
        }
    }

    return false;
}

bool InputMapper::getStateFromActiveContexts(RawButton button,
                                             State& state) const
{
    for(list<InputContext*>::const_iterator i = activeContexts.begin();
        i != activeContexts.end(); i++)
    {
        const InputContext* context = *i;
        if(context->getMappedState(button, state))
        {
            return true;
        }
    }
}

// Calls all of the registered callbacks with a copy of currentInput.
void InputMapper::dispatch() const
{
    // This provides a copy of input. Is this necessary?
    // It allows dispatch to be const, but the callbacks still can't be handled
    // in parallel.
    InputMap input = currentInput;
    for(map<int, InputCallback>::const_iterator i = callbacks.begin();
        i != callbacks.end(); i++)
    {
        (*i->second)(input);
    }
}

// Call this after dispatching to prepare for the next set of input
void InputMapper::reset()
{
    currentInput.actions.clear();
    currentInput.ranges.clear();
}

void InputMapper::clearInputPerButton(RawButton button)
{
    Action action;
    State state;
    
    // Do we need this for actions since actions are removed via reset()?
    // This may affect actions bound to multiple buttons (how?)
    if(getActionFromContext(button, action))
    {
        currentInput.removeAction(action);
    }

    if(getStateFromContext(button, state))
    {
        currentInput.removeState(state);
    }
}
