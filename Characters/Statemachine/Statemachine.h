#ifndef GBFIGHTER_STATEMACHINE_H
#define GBFIGHTER_STATEMACHINE_H

#include "../../Utils/Core.h"
#include "State.h"

// forward declaration of BaseCharacter to avoid circular dependency
class BaseCharacter;

class Statemachine
{
private:
    // Current state (use smart pointers for automatic memory management)
    shared<State> previousState;
    shared<State> currentState;
    shared<State> nextState;
    BaseCharacter& character; // Reference to the owning Character


public:
    Statemachine(BaseCharacter& characterRef);
    void ChangeState(shared<State> newState);
    void Update(float deltaTime);
    State& getCurrentState();
};

#endif //GBFIGHTER_STATEMACHINE_H
