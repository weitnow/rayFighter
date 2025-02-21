#include "InputTypes.h"

std::string directionToString(InputDirection direction)
{
    switch (direction)
    {
    case InputDirection::Neutral:
        return "Neutral";
    case InputDirection::Down:
        return "Down";
    case InputDirection::DownForward:
        return "DownForward";
    case InputDirection::Forward:
        return "Forward";
    case InputDirection::UpForward:
        return "UpForward";
    case InputDirection::Up:
        return "Up";
    case InputDirection::UpBackward:
        return "UpBackward";
    case InputDirection::Backward:
        return "Backward";
    case InputDirection::DownBackward:
        return "DownBackward";
    default:
        return "Unknown";
    }
}

std::string actionToString(InputAction action)
{
    switch (action)
    {
    case InputAction::None:
        return "None";
    case InputAction::Punch:
        return "Punch";
    case InputAction::Kick:
        return "Kick";
    case InputAction::Block:
        return "Block";
    case InputAction::Special:
        return "Special";
    default:
        return "Unknown";
    }
}

const SpecialMove Fireball = {"Fireball",
                              {{InputDirection::Down, InputAction::None},
                               {InputDirection::DownForward, InputAction::None},
                               {InputDirection::Forward, InputAction::None},
                               {InputDirection::Neutral, InputAction::Punch}}};