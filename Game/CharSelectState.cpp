#include "CharSelectState.h"
#include "Game.h"
#include "GameState.h"


CharSelectState::CharSelectState(Game* game) : BaseState(game)
{
}

CharSelectState::~CharSelectState()
{
}

void CharSelectState::Enter()
{
    BaseState::Enter();
}

void CharSelectState::Update(float deltaTime)
{

    //handle input //todo: refactor this to inputHandler
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {

        game->ChangeState(std::make_unique<GameState>(game));
    }
}

void CharSelectState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(GREEN);


    DrawText("CharSelect",
             Constants::RENDERTARGET_WIDTH / 2 - MeasureText("1P Start", 8) / 2,
             105,
             8,
             Constants::RAYFIGHTER_WHITE);


    game->screen2DManager->endDrawToRenderTarget();
    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToScreen();

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    game->screen2DManager->endDrawToScreen();
}


void CharSelectState::Exit()
{
}
