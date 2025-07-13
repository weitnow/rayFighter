#include "IntroState.h"
#include "Game.h"
#include "MenuState.h"


IntroState::IntroState(Game* game) : BaseState(game), IntroScreen(nullptr), timerInMs{8.0f}
{
}

IntroState::~IntroState()
{

    delete IntroScreen;
    IntroScreen = nullptr;


    //game->soundManager->unloadMusic("decisions.mp3");
}

void IntroState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    //game->soundManager->loadMusic("decisions.mp3", 1.f);
    //game->soundManager->playBackgroundMusic("decisions.mp3");

    // load TitleScreen
    IntroScreen = game->asepriteManager->createNewAnimFilePtr("gbIntro");
    IntroScreen->setFrameTag("gbIntro-Intro");
}

void IntroState::Update(float deltaTime)
{
    IntroScreen->update(game->deltaTime);

    timerInMs -= game->deltaTime;

    HandleInput();

    if (timerInMs <= 0.0f)
    {
        game->ChangeState(std::make_unique<MenuState>(game));
    }
}

void IntroState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(BLACK);


    // draw stage
    IntroScreen->drawCurrentSelectedTag(0, 0);


    game->screen2DManager->endDrawToRenderTarget();
    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToScreen();

    ClearBackground(BLACK);

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    // render overlay
    game->screen2DManager->drawOverlay();

    game->screen2DManager->endDrawToScreen();
}

void IntroState::Pause()
{
}

void IntroState::Resume()
{
}


void IntroState::Exit()
{
}

void IntroState::HandleInput()
{
    if (player1Controller->punch || player1Controller->key_enter)
    {
        game->ChangeState(std::make_unique<MenuState>(game));
    }
}
