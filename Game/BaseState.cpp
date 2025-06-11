#include "BaseState.h"
#include "Game.h"

BaseState::BaseState(Game* game)
    : screen2DManager(game->screen2DManager.get()), player1(nullptr), player2(nullptr), game(game),
      soundManager(game->soundManager), inputHandler(game->inputHandler.get()),
      asepriteManager(game->asepriteManager.get()), debugInfo(nullptr),
      player1Controller(game->inputHandler->getPlayer1Controller()),
      player2Controller(game->inputHandler->getPlayer2Controller())
{

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
