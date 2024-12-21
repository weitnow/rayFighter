#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "DebugInfo.h"
#include "raylib.h"
#include <chrono>
#include <deque>


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
    Attack,
    Special
};


struct SpecialMove
{
    std::string name;
    std::vector<std::pair<InputDirection, InputAction>> sequence;
};

const SpecialMove Fireball = {"Fireball",
                              {
                                  {InputDirection::Down, InputAction::None},
                                  {InputDirection::DownForward, InputAction::None},
                                  {InputDirection::Forward, InputAction::None},
                                  {InputDirection::Neutral, InputAction::Attack} // Attack button
                              }};


class InputBuffer
{
public:
    void addInput(InputDirection direction, InputAction action)
    {
        // Add new input with timestamp
        buffer.push_back({direction, action, getCurrentTime()});

        // Remove old inputs outside time window
        while (!buffer.empty() && (getCurrentTime() - buffer.front().timestamp > bufferTimeWindow))
        {
            buffer.pop_front();
        }
    }

    bool matchSequence(const SpecialMove& move)
    {
        if (buffer.size() < move.sequence.size())
        {
            return false;
        }

        auto it = buffer.end() - move.sequence.size();
        for (size_t i = 0; i < move.sequence.size(); ++i, ++it)
        {
            if (it->direction != move.sequence[i].first || it->action != move.sequence[i].second)
            {
                return false;
            }
        }
        return true;
    }

private:
    struct Input
    {
        InputDirection direction;
        InputAction action;
        double timestamp;
    };

    std::deque<Input> buffer;
    const double bufferTimeWindow = 1.0; // Time window in seconds

    double getCurrentTime() const
    {
        return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }
};

// ========================================

struct CharacterController
{
    bool moveLeft = false;
    bool moveRight = false;
    bool jump = false;
    bool duck = false;
    bool punch = false;
    bool kick = false;
    bool block = false;
};


class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    // Delete copy constructor and copy assignment
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;

    void Update();

    void addDebugInfo(DebugInfo& debugInfo);

    CharacterController* const getPlayer1Controller();
    CharacterController* const getPlayer2Controller();

private:
    void _resetBoolsToFalse(CharacterController* controller);
    void _handlePlayer1Input();
    void _handlePlayer2Input();
    void _handleGameInput();

    CharacterController* player1Controller;
    CharacterController* player2Controller;
    DebugInfo* debugInfo;
};

#endif // INPUT_HANDLER_H
