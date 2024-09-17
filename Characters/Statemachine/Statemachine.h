#ifndef GBFIGHTER_STATEMACHINE_H
#define GBFIGHTER_STATEMACHINE_H

#include "../../Utils/Core.h"
#include "State.h"
#include "StateFactory.h"

// forward declaration of BaseCharacter to avoid circular dependency
class BaseCharacter;

class Statemachine
{
private:
    // Current state (use smart pointers for automatic memory management)
    shared<State> previousState;
    shared<State> currentState;
    shared<State> nextState;
    BaseCharacter& character;  // Reference to the owning Character
    StateFactory stateFactory; // Factory to create states-objects - it uses the states defined in State.h

    void _changeStateInternal(shared<State> newState); // called by changeState(std::string newState)

public:
    Statemachine(BaseCharacter& characterRef);
    void changeState(std::string newState);
    void update(float deltaTime);
    State& getCurrentState();
    std::string getCurrentStateAsString();
};


#endif //GBFIGHTER_STATEMACHINE_H
