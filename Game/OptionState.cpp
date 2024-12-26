#include "OptionState.h"
#include "../Constants.h"
#include "Game.h"
#include "GameState.h"


OptionSelectState::OptionSelectState(Game* game) : BaseState(game), OptionSelectScreen(nullptr)
{
    OptionSelectScreen = game->asepriteManager->getAnimFile("optionSelectScreen");
    OptionSelectScreen->setFrameTag("optionSelectScreen-Intro");
}

OptionSelectState::~OptionSelectState()
{

    std::cout << "CharSelectState Destructor called, unloading resources" << std::endl;

    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("sunburn.mp3");
    }


    delete OptionSelectScreen;
}

void OptionSelectState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("sunburn.mp3", 1.f);
        game->soundManager->playBackgroundMusic("sunburn.mp3");
    }
}

void OptionSelectState::Update(float deltaTime)
{
    game->soundManager->updateBackgroundMusic(); // Update Music

    screen2DManager->update(game->deltaTime);

    // Update OptionSelectScreen
    OptionSelectScreen->update(deltaTime);

    if (OptionSelectScreen->getCurrentFrame() == OptionSelectScreen->getMaxFrame())
    {
        OptionSelectScreen->setFrameTag("optionSelectScreen-Idle");
    }

    //handle input //todo: refactor this to inputHandler
    if (IsKeyPressed(KEY_ENTER))
    {

        game->ChangeState(std::make_unique<GameState>(game));
    }

    // check if ESC key is pressed or windows close button is clicked
    if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())
    {
        //pop this state and return to menu
        game->PopState();
    }
}

void OptionSelectState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(GREEN);

    // Draw OptionSelectScreen
    OptionSelectScreen->drawCurrentSelectedTag(0, 0);

    screen2DManager->draw();

    game->screen2DManager->endDrawToRenderTarget();


    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    ClearBackground(BLACK);
    game->screen2DManager->beginDrawToScreen();

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    // render overlay
    game->screen2DManager->drawOverlay();

    game->screen2DManager->endDrawToScreen();
}

void OptionSelectState::Pause()
{
}

void OptionSelectState::Resume()
{
}


void OptionSelectState::Exit()
{
}

void OptionSelectState::HandleInput()
{
}
