#include "CharSelectState.h"
#include "Game.h"
#include "GameState.h"


CharSelectState::CharSelectState(Game* game) : BaseState(game), CharSelectScreen(nullptr)
{
    CharSelectScreen = game->asepriteManager->getAnimFile("charSelectScreen");
    CharSelectScreen->setFrameTag("charSelectScreen-Idle");
}

CharSelectState::~CharSelectState()
{
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("stage1.wav");
    }
}

void CharSelectState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("stage1.wav", 1.f);
        game->soundManager->playBackgroundMusic("stage1.wav");
    }
}

void CharSelectState::Update(float deltaTime)
{
    game->soundManager->updateBackgroundMusic(); // Update Music

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


    // Draw CharSelectScreen
    CharSelectScreen->drawCurrentSelectedTag(0, 0);


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
