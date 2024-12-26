#include "InputHandler.h"

InputDirection mapDirectionInput()
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

InputAction mapActionInput()
{
    if (IsKeyPressed(KEY_J))
    {
        return InputAction::Attack;
    }


    return InputAction::None;
}

void updateInputBuffer(InputBuffer& buffer)
{
    InputDirection direction = mapDirectionInput();
    InputAction action = mapActionInput();

    // Print the detected input direction and action in a readable format
    std::cout << "Direction: " << directionToString(direction) << ", Action: " << actionToString(action) << std::endl;

    buffer.addInput(direction, action);


    buffer.addInput(mapDirectionInput(), mapActionInput());
}

void checkSpecialMoves(InputBuffer& buffer)
{
    if (buffer.matchSequence(Fireball))
    {
        std::cout << "Fireball executed!" << std::endl;
    }
}

InputHandler::InputHandler()
{
    player1Controller = new CharacterController();
    player2Controller = new CharacterController();
}

InputHandler::~InputHandler()
{
    delete player1Controller;
    delete player2Controller;
}

void InputHandler::Update()
{

    updateInputBuffer(inputBuffer);
    checkSpecialMoves(inputBuffer);


    // player 1
    _resetBoolsToFalse(player1Controller);
    _handlePlayer1Input();


    // player 2
    _resetBoolsToFalse(player2Controller);
    _handlePlayer2Input();

    // game controls
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
}

void InputHandler::_handlePlayer1Input()
{
    if (IsKeyDown(KEY_A))
    {
        //gameManager->getBaseCharacter("player1")->moveLeft();
        player1Controller->moveLeft = true;
    }
    else if (IsKeyDown(KEY_D))
    {
        //gameManager->getBaseCharacter("player1")->moveRight();
        player1Controller->moveRight = true;
    }

    if (IsKeyDown(KEY_W))
    {
        //gameManager->getBaseCharacter("player1")->jump();
        player1Controller->jump = true;
    }
    else if (IsKeyDown(KEY_S))
    {
        //gameManager->getBaseCharacter("player1")->duck();
        player1Controller->duck = true;
    }

    if (IsKeyPressed(KEY_J))
    {
        //gameManager->getBaseCharacter("player1")->punch();
        player1Controller->punch = true;
    }
    if (IsKeyPressed(KEY_K))
    {
        //gameManager->getBaseCharacter("player1")->kick();
        player1Controller->kick = true;
    }
    if (IsKeyDown(KEY_L))
    {
        //gameManager->getBaseCharacter("player1")->block();
        player1Controller->block = true;
    }
}

void InputHandler::_handlePlayer2Input()
{
    if (IsKeyDown(KEY_LEFT))
    {
        //gameManager->getBaseCharacter("player2")->moveLeft();
        player2Controller->moveLeft = true;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        //gameManager->getBaseCharacter("player2")->moveRight();
        player2Controller->moveRight = true;
    }

    if (IsKeyDown(KEY_UP))
    {
        //gameManager->getBaseCharacter("player2")->jump();
        player2Controller->jump = true;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        //gameManager->getBaseCharacter("player2")->duck();
        player2Controller->duck = true;
    }

    if (IsKeyPressed(KEY_U))
    {
        //gameManager->getBaseCharacter("player2")->punch();
        player2Controller->punch = true;
    }
    if (IsKeyPressed(KEY_I))
    {
        //gameManager->getBaseCharacter("player2")->kick();
        // not implemented yet
    }
    if (IsKeyDown(KEY_O))
    {
        //gameManager->getBaseCharacter("player2")->block();
        player2Controller->block = true;
    }
}

void InputHandler::_handleGameInput()
{
    if (IsKeyPressed(KEY_Q))
    {
        Global::debugMode = !Global::debugMode;

        debugInfo->setDebugMode(Global::debugMode);
    }
}
