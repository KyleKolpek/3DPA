#ifndef INPUTMAPPER_H
#define INPUTMAPPER_H

#include <list>
#include <map>
#include <set>
#include <string>
#include "InputConstants.h"
#include "RawInputConstants.h"

class InputContext;
class Updatable;

class InputMap
{
public:
    std::set<Input::Action> actions;
    std::set<Input::State> states;
    std::map<Input::Range, float> ranges;
    std::string text;

    void removeAction(Input::Action action);
    void removeState(Input::State state);
    void removeRange(Input::Range range);
};

class InputMapper
{
public:
    InputMapper();
    ~InputMapper();
    
    void addCallback(Updatable *callback, int priority);
    void pushContext(const std::string& contextName);
    void popContext();

    bool getActionFromActiveContexts(Input::RawButton button,
                                     Input::Action& action) const;
    bool getStateFromActiveContexts(Input::RawButton button,
                                    Input::State& state) const;

    void processButtonInput(Input::RawButton button, bool pressed, bool repeat);
    void processAxisInput(Input::RawAxis axis, float value);
    void processTextInput(char *c);

    void dispatch() const;
    void reset();
    void clearInputPerButton(Input::RawButton button);

protected:
private:
    std::map<std::string, InputContext*> inputContexts;
    std::list<InputContext*> activeContexts;
    std::multimap<int, Updatable*> callbacks;
    InputMap currentInput;
};

#endif
