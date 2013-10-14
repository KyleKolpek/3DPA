#ifndef INPUTMAPPER_H
#define INPUTMAPPER_H

#include <list>
#include <map>
#include <set>
#include "InputConstants.h"

class InputContext;

class InputMap
{
public:
    std::set<Action> actions;
    std::set<State> states;
    std::map<Range, float> ranges;

    void removeAction(Action action);
    void removeState(State state);
    void removeRange(Range range);
};

class InputMapper
{
public:
    InputMapper();
    ~InputMapper();
    
    // NOTE: This may be better represented as an interface
    typedef void (*InputCallback)(InputMap&);
    void addCallback(InputCallback callback, int priority);
    void pushContext(const string& contextName);
    void popContext();

    bool getActionFromActiveContexts(RawButton button, Action& action) const;
    bool getStateFromActiveContexts(RawButton button, State& state) const;

    void processButtonInput(RawButton button,
                            bool pressed,
                            bool previouslyPressed);
    void processAxisInput(RawAxis axis, float value);

    void dispatch() const;
    void reset();
    void clearInputPerButton(RawButton button);

protected:
private:
    std::map<std::string, InputContext*> inputContexts;
    std::list<InputContext*> activeContexts;
    std::multimap<int, InputCallback> callbacks;
    InputMap currentInput;
};

#endif
