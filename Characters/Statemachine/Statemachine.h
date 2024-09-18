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
    BaseCharacter& character;       // Reference to the owning Character
    StateFactory stateFactory;      // Factory to create states-objects - it uses the states defined in State.h
    BaseCharacter* owner = nullptr; // Pointer to the BaseCharacter owning this Statemachine

    void _changeStateInternal(shared<State> newState); // called by changeState(std::string newState)

public:
    Statemachine(BaseCharacter& characterRef);
    void changeState(std::string newState);
    void update(float deltaTime); // Update the current state (calls State::Update)
    State& getCurrentState();
    std::string getCurrentStateAsString();
    std::string getPreviousStateAsString();

    void setOwner(BaseCharacter* owner) // Set the owner of this Statemachine (BaseCharacter, for example Player 1)
    {
        this->owner = owner;
        stateFactory.setOwner(owner);
    }
};


#endif //GBFIGHTER_STATEMACHINE_H
