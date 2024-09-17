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

public:
    shared<State> getState(const std::string& stateName)
    {
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
        else if (stateName == "Duck")
        {
            newState = std::make_shared<DuckState>();
        }
        else if (stateName == "Punch")
        {
            newState = std::make_shared<PunchState>();
        }
        else
        {
            throw std::invalid_argument("Unknown state name");
        }

        // Store the newly created state in the map and return it
        stateMap[stateName] = newState;
        return newState;
    }
};

#endif // GBFIGHTER_STATEFACTORY_H
