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
                              {{InputDirection::Down, InputAction::None},
                               {InputDirection::DownForward, InputAction::None},
                               {InputDirection::Forward, InputAction::None}}};


class InputBuffer
{
public:
    void addInput(InputDirection direction, InputAction action)
    {
        // If the new input matches the last input, increment its frame count
        if (!buffer.empty() && buffer.back().direction == direction)
        {
            buffer.back().frames++;
        }
        else
        {
            // Otherwise add new input state
            buffer.push_back({direction, action, 1});
        }

        // Keep buffer size manageable
        if (buffer.size() > BUFFER_SIZE)
        {
            buffer.erase(buffer.begin());
        }
    }

    bool matchSequence(const SpecialMove& move)
    {
        int moveIndex = move.sequence.size() - 1; // Start from end of desired sequence
        int bufferIndex = buffer.size() - 1;      // Start from most recent input

        while (moveIndex >= 0 && bufferIndex >= 0)
        {
            const auto& requiredInput = move.sequence[moveIndex];
            const auto& currentInput = buffer[bufferIndex];

            if (currentInput.direction == requiredInput.first)
            {
                moveIndex--; // Found a match, look for next required input
            }
            else if (currentInput.frames > MAX_LENIENCY_FRAMES)
            {
                // If we've held this non-matching input too long, sequence fails
                return false;
            }

            bufferIndex--;
        }

        return moveIndex < 0; // Did we match all required inputs?
    }

private:
    struct Input
    {
        InputDirection direction;
        InputAction action;
        int frames; // how many frames this input has been held
    };
    static const int BUFFER_SIZE = 60;         // Store last 60 frames of input
    static const int MAX_LENIENCY_FRAMES = 15; // Allow holding a direction up to 15 frames
    std::deque<Input> buffer;
};

InputDirection mapDirectionInput();

InputAction mapActionInput();

void updateInputBuffer(InputBuffer& buffer);

void checkSpecialMoves(InputBuffer& buffer);

std::string directionToString(InputDirection direction);

std::string actionToString(InputAction action);

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

    InputBuffer inputBuffer;
};

#endif // INPUT_HANDLER_H
