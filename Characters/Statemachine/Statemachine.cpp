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

void Statemachine::init(const Dictionary<std::string, std::shared_ptr<State>>& customStateMap)
{
    // Populate the stateMap with the customStateMap and set the owner for each state
    _populateStateMap(customStateMap);
    _setOwnerForStates();
}

void Statemachine::setOpponent(BaseCharacter* opponent)
{
    this->opponent = opponent;

    // setting opponent for each state-obj in statemap
    for (auto& [name, state] : stateMap)
    {
        state->setOpponent(opponent);
    }
}

void Statemachine::setGameState(GameState* gameState)
{
    this->gameState = gameState;

    // setting gameState for each state-obj in statemap
    for (auto& [name, state] : stateMap)
    {
        state->setGameState(gameState);
    }
}

void Statemachine::_populateStateMap(const Dictionary<std::string, std::shared_ptr<State>>& customStateMap)
{
    stateMap = customStateMap;
}

Dictionary<std::string, std::shared_ptr<State>> Statemachine::getDefaultStateMap()
{

    Dictionary<std::string, std::shared_ptr<State>> customStateMap = {{"Idle", std::make_shared<IdleState>()},
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

    return customStateMap;
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

GameState* Statemachine::getGameState()
{
    // raise error if nullptr
    if (gameState == nullptr)
    {
        throw std::runtime_error("Statemachine::getGameState() -> GameState is nullptr");
    }
    return gameState;
}

BaseCharacter* Statemachine::getOwner()
{
    // raise error if nullptr
    if (owner == nullptr)
    {
        throw std::runtime_error("Statemachine::getOwner() -> Owner is nullptr");
    }
    return owner;
}

BaseCharacter* Statemachine::getOpponent()
{
    // raise error if nullptr
    if (opponent == nullptr)
    {
        throw std::runtime_error("Statemachine::getOpponent() -> Opponent is nullptr");
    }
    return opponent;
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
