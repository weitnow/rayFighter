#ifndef INPUT_TYPES_H
#define INPUT_TYPES_H

#include <string>
#include <utility>
#include <vector>

enum class InputDirection
{
    Neutral,     // No input
    Down,        // ↓
    DownForward, // ↘
    Forward,     // →
    UpForward,   // ↗
    Up,          // ↑
    UpBackward,  // ↖
    Backward,    // ←
    DownBackward // ↙
};

enum class InputAction
{
    None,
    Punch,
    Kick,
    Block,
    Special
};

struct SpecialMove
{
    std::string name;
    std::vector<std::pair<InputDirection, InputAction>> sequence;
};

// Move string conversion declarations here
std::string directionToString(InputDirection direction);
std::string actionToString(InputAction action);

extern const SpecialMove Fireball;

#endif // INPUT_TYPES_H
