#include "InputHandler.h"


InputHandler::InputHandler()
{
    player1Controller = new CharacterController();
    player2Controller = new CharacterController();

    // Initialize the key-command map
    keyCommandMap = {
        // player 1 controls
        {KEY_A, {InputCheckType::Down, [this]() { player1Controller->moveLeft = true; }}},
        {KEY_D, {InputCheckType::Down, [this]() { player1Controller->moveRight = true; }}},
        {KEY_W, {InputCheckType::Down, [this]() { player1Controller->jump = true; }}},
        {KEY_S, {InputCheckType::Down, [this]() { player1Controller->duck = true; }}},
        {KEY_J, {InputCheckType::Pressed, [this]() { player1Controller->punch = true; }}},
        {KEY_K, {InputCheckType::Pressed, [this]() { player1Controller->kick = true; }}},
        {KEY_L, {InputCheckType::Down, [this]() { player1Controller->block = true; }}},
        {KEY_ENTER, {InputCheckType::Pressed, [this]() { player1Controller->key_enter = true; }}},
        {KEY_ESCAPE, {InputCheckType::Pressed, [this]() { player1Controller->key_esc = true; }}},
        {KEY_Q, {InputCheckType::Pressed, [this]() { player1Controller->key_q = true; }}},

        {GAMEPAD_BUTTON_LEFT_FACE_DOWN, {InputCheckType::Down, [this]() { player1Controller->duck = true; }}},
        {GAMEPAD_BUTTON_LEFT_FACE_RIGHT, {InputCheckType::Down, [this]() { player1Controller->jump = true; }}},
        {GAMEPAD_BUTTON_LEFT_FACE_LEFT, {InputCheckType::Down, [this]() { player1Controller->block = true; }}},
        {GAMEPAD_BUTTON_RIGHT_FACE_DOWN, {InputCheckType::Down, [this]() { player1Controller->punch = true; }}},
        {GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, {InputCheckType::Down, [this]() { player1Controller->kick = true; }}},
        {GAMEPAD_BUTTON_LEFT_TRIGGER_1, {InputCheckType::Down, [this]() { player1Controller->moveLeft = true; }}},
        {GAMEPAD_BUTTON_RIGHT_TRIGGER_1, {InputCheckType::Down, [this]() { player1Controller->moveRight = true; }}},

        // player 2 controls
        {KEY_LEFT, {InputCheckType::Down, [this]() { player2Controller->moveLeft = true; }}},
        {KEY_RIGHT, {InputCheckType::Down, [this]() { player2Controller->moveRight = true; }}},
        {KEY_UP, {InputCheckType::Down, [this]() { player2Controller->jump = true; }}},
        {KEY_DOWN, {InputCheckType::Down, [this]() { player2Controller->duck = true; }}},
        {KEY_U, {InputCheckType::Pressed, [this]() { player2Controller->punch = true; }}},
        {KEY_I, {InputCheckType::Pressed, [this]() { player2Controller->kick = true; }}},
        {KEY_O, {InputCheckType::Down, [this]() { player2Controller->block = true; }}},
    };
};

InputHandler::~InputHandler()
{
    delete player1Controller;
    delete player2Controller;
}

void InputHandler::Update()
{
    //Todo: uncomment this
    //updateInputBuffer(inputBuffer);
    //checkSpecialMoves(inputBuffer);

    _resetBoolsToFalse(player1Controller);
    _resetBoolsToFalse(player2Controller);
    _handleGameInput();
}


void InputHandler::addDebugInfo(DebugInfo& debugInfo)
{
    this->debugInfo = &debugInfo;
}

CharacterController* const InputHandler::getPlayer2Controller()
{
    return player2Controller;
}

CharacterController* const InputHandler::getPlayer1Controller()
{
    return player1Controller;
}

void InputHandler::_resetBoolsToFalse(CharacterController* controller)
{
    controller->moveLeft = false;
    controller->moveRight = false;
    controller->jump = false;
    controller->duck = false;
    controller->punch = false;
    controller->kick = false;
    controller->block = false;
    // general input
    controller->key_esc = false;
    controller->key_enter = false;
    controller->key_q = false;
}

void InputHandler::_handleGameInput()
{
    // Iterate over the keyCommandMap
    for (const auto& [key, inputCommand] : keyCommandMap)
    {
        if ((inputCommand.checkType == InputCheckType::Pressed && (IsKeyPressed(key)) ||
             IsGamepadButtonPressed(0, key)) ||
            (inputCommand.checkType == InputCheckType::Down && (IsKeyDown(key)) || IsGamepadButtonDown(0, key)))
        {
            inputCommand.command();
        }
    }
}

InputDirection InputHandler::mapDirectionInput()
{
    if (IsKeyDown(KEY_S))
    {
        if (IsKeyDown(KEY_D))
            return InputDirection::DownForward;
        if (IsKeyDown(KEY_A))
            return InputDirection::DownBackward;
        return InputDirection::Down;
    }
    if (IsKeyDown(KEY_W))
    {
        if (IsKeyDown(KEY_D))
            return InputDirection::UpForward;
        if (IsKeyDown(KEY_A))
            return InputDirection::UpBackward;
        return InputDirection::Up;
    }
    if (IsKeyDown(KEY_D))
        return InputDirection::Forward;
    if (IsKeyDown(KEY_A))
        return InputDirection::Backward;
    return InputDirection::Neutral;
}

InputAction InputHandler::mapActionInput()
{
    if (IsKeyPressed(KEY_J))
    {
        return InputAction::Attack;
    }


    return InputAction::None;
}

void InputHandler::updateInputBuffer(InputBuffer& buffer)
{
    InputDirection direction = mapDirectionInput();
    InputAction action = mapActionInput();

    // Print the detected input direction and action in a readable format
    std::cout << "Direction: " << directionToString(direction) << ", Action: " << actionToString(action) << std::endl;

    buffer.addInput(direction, action);


    buffer.addInput(mapDirectionInput(), mapActionInput());
}

void InputHandler::checkSpecialMoves(InputBuffer& buffer)
{
    if (buffer.matchSequence(Fireball))
    {
        std::cout << "Fireball executed!" << std::endl;
    }
}
