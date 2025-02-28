#include "Statemachine.h"
#include "../BaseCharacter.h"
#include <string>


Statemachine::Statemachine() : previousState(nullptr), currentState(nullptr), owner(nullptr)
{
    populateStateMap();
}

void Statemachine::populateStateMap()
{
    // Check if the StateFactory has an owner
    /*
    if (!owner)
    {
        throw std::runtime_error("StateFactory::getState() -> Owner is not set.");
    }
    */
    stateMap = {{"Idle", std::make_shared<IdleState>()},
                {"Walk", std::make_shared<WalkState>()},
                {"Jump", std::make_shared<JumpState>()},
                {"JumpPunch", std::make_shared<JumpPunchState>()},
                {"Duck", std::make_shared<DuckState>()},
                {"DuckPunch", std::make_shared<DuckPunchState>()},
                {"DuckKick", std::make_shared<DuckKickState>()},
                {"DuckBlock", std::make_shared<DuckBlockState>()},
                {"Punch", std::make_shared<PunchState>()},
                {"Kick", std::make_shared<KickState>()},
                {"Block", std::make_shared<BlockState>()},
                {"Hit", std::make_shared<HitState>()},
                {"Hurt", std::make_shared<HurtState>()},
                {"Death", std::make_shared<DeathState>()}};

    //std::shared_ptr<State> myState = stateMap["Walk"];
    //std::cout << myState->stateName << std::endl;
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

void Statemachine::setOwner(BaseCharacter* owner)
{
    this->owner = owner;

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
