#include "BaseState.h"
#include "Game.h"

BaseState::BaseState(Game* game) : game(game)
{

    screen2DManager = game->screen2DManager;
    soundManager = game->soundManager;
    inputHandler = game->inputHandler;
    asepriteManager = game->asepriteManager;
    debugInfo = nullptr;
    gameManager = game->gameManager;
    player1 = nullptr;
    player2 = nullptr;
    collisionManager = nullptr;
    player1Controller = game->inputHandler->getPlayer1Controller();
    player2Controller = game->inputHandler->getPlayer2Controller();
}

BaseState::~BaseState()
{
}

void BaseState::Enter()
{
}

void BaseState::Pause()
{
}
