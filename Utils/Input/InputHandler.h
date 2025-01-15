#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "CharacterController.h"
#include "DebugInfo.h"
#include "InputBuffer.h"
#include "InputTypes.h"
#include "raylib.h"
#include <deque>
#include <unordered_map>


enum class InputCheckType
{
    Pressed,
    Down
};

struct InputCommand
{
    InputCheckType checkType;
    std::function<void()> command;
};

// Define a type alias for the key-command map
using KeyCommandMap = std::unordered_map<int, InputCommand>;

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

    // Check if a specific key was just pressed
    bool isKeyJustPressed(const CharacterController& current);


private:
    void _resetBoolsToFalse(CharacterController* controller);
    void _handleGameInput();

    InputDirection mapDirectionInput();
    InputAction mapActionInput();
    void updateInputBuffer(InputBuffer& buffer);
    void checkSpecialMoves(InputBuffer& buffer);

    CharacterController* player1Controller;
    CharacterController* player2Controller;
    // previous controller state from last frame for comparison
    CharacterController prevPlayer1Controller;
    CharacterController prevPlayer2Controller;


    DebugInfo* debugInfo;
    InputBuffer inputBuffer;

    KeyCommandMap keyCommandMap;
};

#endif // INPUT_HANDLER_H
