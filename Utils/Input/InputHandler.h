#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "../../Characters/BaseCharacter.h"
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
    void addPlayer(BaseCharacter* player, int playerNumber);


    CharacterController* const getPlayer1Controller();
    CharacterController* const getPlayer2Controller();

    // Check if a specific key was just pressed
    bool isKeyJustPressed(const CharacterController& current);


private:
    void _resetBoolsToFalse(CharacterController* controller);
    void _handleGameInput();

    InputDirection _mapDirectionInput(CharacterController* controller);
    InputAction _mapActionInput(CharacterController* controller);
    void updateInputBuffer(InputBuffer& buffer, CharacterController* controller);
    void checkSpecialMoves(InputBuffer& buffer, CharacterController* controller, BaseCharacter* player);

    CharacterController* player1Controller;
    CharacterController* player2Controller;
    // previous controller state from last frame for comparison
    CharacterController prevPlayer1Controller; //used in InputHandler::isKeyJustPressed for checking if key just pressed
    CharacterController prevPlayer2Controller; //used in InputHandler::isKeyJustPressed for checking if key just pressed

    void checkIfGamepadIsConnected();

    int GamepadCheckConnectionDone; // Required for gamepad connection checking
    bool Gamepad0Connected;
    bool Gamepad1Connected;

    DebugInfo* debugInfo;
    InputBuffer player1InputBuffer;
    InputBuffer player2InputBuffer;

    BaseCharacter* player1;
    BaseCharacter* player2;

    KeyCommandMap keyCommandMap;
};

#endif // INPUT_HANDLER_H
