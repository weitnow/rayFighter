#include "Statemachine.h"
#include "../BaseCharacter.h"
#include <string>

Statemachine::Statemachine(BaseCharacter& characterRef)
    : character(characterRef), currentState(nullptr), previousState(nullptr), nextState(nullptr)
{
}

void Statemachine::_changeStateInternal(shared<State> newState)
{
    // check if the new state is the same as the current state
    if (currentState == newState)
    {
        // if it is the same, do nothing and return
        return;
    }


    // Finalize the current state if it exists
    if (currentState)
    {
        currentState->Finalize();
    }

    // Save the current state as the previous state
    previousState = currentState;

    // Change to the new state
    currentState = newState;

    // Initialize the new state
    if (currentState)
    {
        currentState->Init();
    }
}

void Statemachine::changeState(std::string newState)
{
    _changeStateInternal(stateFactory.getState(newState));
}

void Statemachine::update(float deltaTime)
{
    if (currentState)
    {
        currentState->Update(deltaTime);
    }
}

State& Statemachine::getCurrentState()
{
    if (currentState)
    {
        return *currentState;
    }
    else
    {
        throw std::runtime_error("Statemachine::getCurrentState() -> Current state is not set.");
    }
}

std::string Statemachine::getCurrentStateAsString()
{
    if (currentState)
    {
        return currentState->stateName;
    }
    else
    {
        return "No state";
    }
}
