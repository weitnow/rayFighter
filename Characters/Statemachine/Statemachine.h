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
    BaseCharacter* owner; // Pointer to the BaseCharacter owning this Statemachine

    // Key: State name, Value: State instance
    Dictionary<std::string, shared<State>> stateMap;


public:
    Statemachine();
    void changeState(std::string newStateName);
    void update(float deltaTime); // Update the current state (calls State::Update)
    State& getCurrentState();
    std::string getCurrentStateAsString();
    std::string getPreviousStateAsString();
    void setOwner(BaseCharacter* owner); // Set the owner of this Statemachine (BaseCharacter, for example Player 1)

    void populateStateMap();
};


#endif //GBFIGHTER_STATEMACHINE_H
