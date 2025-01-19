#include "OptionState.h"
#include "../Constants.h"
#include "Game.h"
#include "GameState.h"

const char* resolutionOptions[] = {"640x480", "800x600", "1280x720", "1920x1080", "2560x1440", "3440x1440", "Auto"};

OptionSelectState::OptionSelectState(Game* game) : BaseState(game), OptionSelectScreen(nullptr), selectedOption{6}
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

    screen2DManager->fadeEffect(0.6f, 0.f);
}

void OptionSelectState::Update(float deltaTime)
{

    // Update OptionSelectScreen
    OptionSelectScreen->update(deltaTime);

    if (OptionSelectScreen->getCurrentFrame() == OptionSelectScreen->getMaxFrame())
    {
        OptionSelectScreen->setFrameTag("optionSelectScreen-Idle");
    }


    HandleInput();
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

    // Draw availabe Screenresolution
    _renderOptionMenu();

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
    if (player1Controller->kick)
    {
        //pop this state and return to menu
        game->PopState();
    }

    if (player1Controller->punch || player2Controller->punch)
    {
        std::cout << "player 1 or 2 punching " << std::endl;
    }
}

void OptionSelectState::_renderOptionMenu()
{
    DrawText("Resolution",
             Constants::RENDERTARGET_WIDTH / 2 - MeasureText("Resolution", 8) / 2,
             50,
             8,
             Constants::RAYFIGHTER_WHITE);

    for (int i = 0; i < 7; i++)
    {
        Color color = (i == selectedOption) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
        DrawText(resolutionOptions[i],
                 Constants::RENDERTARGET_WIDTH / 2 - MeasureText(resolutionOptions[i], 8) / 2,
                 65 + i * 10,
                 8,
                 color);
    }
}
