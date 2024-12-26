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

    if (Constants::BACKGROUND_MUSIC)
    {
        //game->soundManager->unloadMusic("decisions.mp3");
    }
}

void IntroState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        //game->soundManager->loadMusic("decisions.mp3", 1.f);
        //game->soundManager->playBackgroundMusic("decisions.mp3");
    }


    // load TitleScreen
    IntroScreen = game->asepriteManager->getAnimFile("gbIntro");
    IntroScreen->setFrameTag("gbIntro-Intro");
}

void IntroState::Update(float deltaTime)
{
    //game->inputHandler->Update();                // Handle Input
    //game->soundManager->updateBackgroundMusic(); // Update Music

    //handle input

    // check if ESC key is pressed or windows close button is clicked
    if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())
    {
        game->quit = true;
    }

    IntroScreen->update(game->deltaTime);


    timerInMs -= game->deltaTime;


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
}
