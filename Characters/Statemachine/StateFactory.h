#ifndef GBFIGHTER_STATEFACTORY_H
#define GBFIGHTER_STATEFACTORY_H

#include "../../Utils/Core.h"
#include "State.h"
#include <stdexcept>
#include <string>

class StateFactory
{
private:
    // Key: State name, Value: State instance
    Dictionary<std::string, shared<State>> stateMap;

    BaseCharacter* owner = nullptr; // Pointer to the BaseCharacter owning this StateFactory

public:
    shared<State> getState(const std::string& stateName)
    {
        // Check if the StateFactory has an owner
        if (!owner)
        {
            throw std::runtime_error("StateFactory::getState() -> Owner is not set.");
        }

        // Check if the state already exists
        auto it = stateMap.find(stateName);
        if (it != stateMap.end())
        {
            return it->second;
        }

        // Create a new state based on the stateName
        shared<State> newState;
        if (stateName == "Idle")
        {
            newState = std::make_shared<IdleState>();
        }
        else if (stateName == "Walk")
        {
            newState = std::make_shared<WalkState>();
        }
        else if (stateName == "Jump")
        {
            newState = std::make_shared<JumpState>();
        }
        else if (stateName == "JumpPunch")
        {
            newState = std::make_shared<JumpPunchState>();
        }
        else if (stateName == "Duck")
        {
            newState = std::make_shared<DuckState>();
        }
        else if (stateName == "DuckPunch")
        {
            newState = std::make_shared<DuckPunchState>();
        }
        else if (stateName == "DuckKick")
        {
            newState = std::make_shared<DuckKickState>();
        }
        else if (stateName == "DuckBlock")
        {
            newState = std::make_shared<DuckBlockState>();
        }
        else if (stateName == "Punch")
        {
            newState = std::make_shared<PunchState>();
        }
        else if (stateName == "Kick")
        {
            newState = std::make_shared<KickState>();
        }
        else if (stateName == "Block")
        {
            newState = std::make_shared<BlockState>();
        }
        else if (stateName == "Hit")
        {
            newState = std::make_shared<HitState>();
        }
        else if (stateName == "Hurt")
        {
            newState = std::make_shared<HurtState>();
        }
        else if (stateName == "Death")
        {
            newState = std::make_shared<DeathState>();
        }
        else
        {
            throw std::invalid_argument(stateName + " is Unknown state name");
        }

        // Set the owner of the new state
        newState->setOwner(owner);

        // Store the newly created state in the map and return it
        stateMap[stateName] = newState;
        return newState;
    }

    void setOwner(BaseCharacter* owner)
    {
        this->owner = owner;
    }
};

#endif // GBFIGHTER_STATEFACTORY_H
