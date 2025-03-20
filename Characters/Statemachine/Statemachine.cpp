#include "Statemachine.h"
#include "../BaseCharacter.h"
#include <string>


Statemachine::Statemachine(BaseCharacter* owner)
    : previousState(nullptr), currentState(nullptr), owner(nullptr), opponent(nullptr), gameState(nullptr)
{

    if (owner == nullptr)
    {
        //raise exception
        throw std::runtime_error("Statemachine::setOwner() -> Owner is nullptr");
    }


    this->owner = owner;
}

void Statemachine::init(const Dictionary<std::string, std::shared_ptr<State>>& customStateMap, GameState* gameState)
{
    // Populate the stateMap with the customStateMap and set the owner for each state
    _populateStateMap(customStateMap);
    _setOwnerForStates();
    this->gameState = gameState;
}

void Statemachine::_populateStateMap(const Dictionary<std::string, std::shared_ptr<State>>& customStateMap)
{
    stateMap = customStateMap;
}


void Statemachine::changeState(std::string newStateName)
{
    // Find the new state in the stateMap
    auto it = stateMap.find(newStateName);

    // If state is not found, through an error
    if (it == stateMap.end())
    {
        return;
        //throw std::runtime_error("Statemachine::stateMap[" + newStateName + "] not found");
    }

    // Get the new state
    std::shared_ptr<State> newState = it->second;

    // If the new state is the same as the current state, return early
    if (currentState == newState)
    {
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

std::string Statemachine::getPreviousStateAsString()
{
    if (previousState)
    {
        return previousState->stateName;
    }
    else
    {
        return "No previous state";
    }
}

void Statemachine::_setOwnerForStates()
{
    // setting owner for each state-obj in statemap
    for (auto& [name, state] : stateMap)
    {
        state->setOwner(owner);
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
        return "No current state";
    }
}
