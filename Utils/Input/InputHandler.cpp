#include "InputHandler.h"


InputHandler::InputHandler()
    : Gamepad0Connected(false), Gamepad1Connected(false), GamepadCheckConnectionDone(5), player1(nullptr),
      player2(nullptr)
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
        {GAMEPAD_BUTTON_LEFT_FACE_RIGHT, {InputCheckType::Down, [this]() { player1Controller->moveRight = true; }}},
        {GAMEPAD_BUTTON_LEFT_FACE_LEFT, {InputCheckType::Down, [this]() { player1Controller->moveLeft = true; }}},
        {GAMEPAD_BUTTON_LEFT_FACE_UP, {InputCheckType::Down, [this]() { player1Controller->jump = true; }}},
        {GAMEPAD_BUTTON_RIGHT_FACE_DOWN, {InputCheckType::Pressed, [this]() { player1Controller->punch = true; }}},
        {GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, {InputCheckType::Pressed, [this]() { player1Controller->kick = true; }}},
        {GAMEPAD_BUTTON_LEFT_TRIGGER_1, {InputCheckType::Down, [this]() { player1Controller->block = true; }}},
        {GAMEPAD_BUTTON_RIGHT_TRIGGER_1, {InputCheckType::Down, [this]() { player1Controller->block = true; }}},

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
    // Store the current state as the previous state, note: it is not a pointer
    prevPlayer1Controller = *player1Controller;
    prevPlayer2Controller = *player2Controller;

    // check if gamepad is connected
    checkIfGamepadIsConnected();

    // Reset the input states for the next frame
    _resetBoolsToFalse(player1Controller);
    _resetBoolsToFalse(player2Controller);

    // Handle game input ----------- //
    _handleGameInput(); // this will set the bools in player1Controller and player2Controller to true if the key is pressed


    if (player1 == nullptr || player2 == nullptr)
    {
        return;
    }
    else
    {
        // Update the input buffer and check for special moves
        updateInputBuffer(player1InputBuffer, player1Controller);
        checkSpecialMoves(player1InputBuffer, player1Controller, player1);

        // TODO: uncomment this code
        //updateInputBuffer(player2InputBuffer, player2Controller);
        //checkSpecialMoves(player2InputBuffer, player2Controller, player2);
    }
}


void InputHandler::addDebugInfo(DebugInfo& debugInfo)
{
    this->debugInfo = &debugInfo;
}

void InputHandler::addPlayer(BaseCharacter* player, int playerNumber)
{
    if (playerNumber == 1)
    {
        player1 = player;
    }
    else if (playerNumber == 2)
    {
        player2 = player;
    }
}


CharacterController* const InputHandler::getPlayer2Controller()
{
    return player2Controller;
}

bool InputHandler::isKeyJustPressed(const CharacterController& current)
{

    // if the current CharacterController is player1Controller, then compare with prevPlayer1Controller otherwise with prevPlayer2Controller
    const CharacterController& previous =
        (&current == player1Controller) ? prevPlayer1Controller : prevPlayer2Controller;

    if (!previous.moveLeft && current.moveLeft || !previous.moveRight && current.moveRight ||
        !previous.jump && current.jump || !previous.duck && current.duck)
    {
        return true;
    }
    return false;
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

    // specialmoves
    controller->fireball = false;
    controller->spear = false;

    // settings which are overriden by BaseCharacter, dont reset them here!
    //controller->isLeft = false; //

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
        if ((inputCommand.checkType == InputCheckType::Pressed &&
             ((IsKeyPressed(key)) || IsGamepadButtonPressed(0, key))) ||
            (inputCommand.checkType == InputCheckType::Down && ((IsKeyDown(key)) || IsGamepadButtonDown(0, key))))
        {
            inputCommand.command();
        }
    }
}

InputDirection InputHandler::_mapDirectionInput(CharacterController* controller)
{

    // Determine forward and backward based on character position
    bool forward = controller->isLeft ? controller->moveRight : controller->moveLeft;
    bool backward = controller->isLeft ? controller->moveLeft : controller->moveRight;

    if (controller->duck)
    {
        if (forward)
            return InputDirection::DownForward;
        if (backward)
            return InputDirection::DownBackward;
        return InputDirection::Down;
    }

    if (controller->jump)
    {
        if (forward)
            return InputDirection::UpForward;
        if (backward)
            return InputDirection::UpBackward;
        return InputDirection::Up;
    }

    if (forward)
        return InputDirection::Forward;

    if (backward)
        return InputDirection::Backward;

    return InputDirection::Neutral; // No input
}

InputAction InputHandler::_mapActionInput(CharacterController* controller)
{
    if (controller->punch && controller->kick)
    {
        return InputAction::Special;
    }

    if (controller->punch)
    {
        return InputAction::Punch;
    }
    if (controller->kick)
    {
        return InputAction::Kick;
    }
    if (controller->block)
    {
        return InputAction::Block;
    }

    return InputAction::None;
}

void InputHandler::updateInputBuffer(InputBuffer& buffer, CharacterController* controller)
{
    InputDirection direction = _mapDirectionInput(controller); // returns ex. InputDirection::DownForward
    InputAction action = _mapActionInput(controller);          // returns ex. InputAction::Punch

    // Print the detected input direction and action in a readable format
    //std::cout << "Direction: " << directionToString(direction) << ", Action: " << actionToString(action) << std::endl;

    buffer.addInput(direction,
                    action); // this adds ex. [InputDirection::DownForward, InputAction::Punch] to the buffer

    //buffer.addInput(_mapDirectionInput(controller), _mapActionInput(controller));
}

void InputHandler::checkSpecialMoves(InputBuffer& buffer, CharacterController* controller, BaseCharacter* player)
{
    // Check if the input buffer matches any special move sequence
    for (const auto& specialMove : player->getSpecialMoves())
    {
        if (buffer.matchSequence(specialMove))
        {
            std::cout << "InputHandler: " << specialMove.name << " executed!" << std::endl;

            // clear buffer
            //otherwise the player can keep holding down the last needed input and the specialmove is executed again and again
            buffer.clearBuffer();
            controller->fireball = true;
        }
    }
}


void InputHandler::checkIfGamepadIsConnected()
{


    if (GamepadCheckConnectionDone <= 0)
    {
        return;
    }
    std::cout << "Checking for Gamepads, remaining trials: " << GamepadCheckConnectionDone << std::endl;

    GamepadCheckConnectionDone--;

    if (IsGamepadAvailable(0))
    {
        Gamepad0Connected = true;
        std::cout << "Gamepad0 is connected" << std::endl;
        std::cout << "Gamepad found, stop trying to connect" << std::endl;
        GamepadCheckConnectionDone = 0;
    }
    else
    {
        Gamepad0Connected = false;
        std::cout << "Gamepad0 is not connected" << std::endl;
    }
    if (IsGamepadAvailable(1))
    {
        Gamepad1Connected = true;
        std::cout << "Gamepad1 is connected" << std::endl;
    }
    else
    {
        Gamepad1Connected = false;
        std::cout << "Gamepad1 is not connected" << std::endl;
    }
}
