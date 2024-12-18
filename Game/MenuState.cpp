#include "MenuState.h"
#include "CharSelectState.h"
#include "Game.h"
#include "OptionState.h"


MenuState::MenuState(Game* game)
    : BaseState(game), aafTitleScreen(nullptr), gameAboutToStart(false), timerInMs{3.0f}, deadSoundPlayed(false)
{
}

MenuState::~MenuState()
{

    delete aafTitleScreen;
    aafTitleScreen = nullptr;

    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("decisions.mp3");
    }
}

void MenuState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("decisions.mp3", 1.f);
        game->soundManager->playBackgroundMusic("decisions.mp3");
    }
    selectedOption = MenuOptions::PLAY;

    // load TitleScreen
    aafTitleScreen = game->asepriteManager->getAnimFile("titleScreen");
    aafTitleScreen->setFrameTag("titleScreen-Titlescreen");
}

void MenuState::Update(float deltaTime)
{
    //game->inputHandler->Update();                // Handle Input //todo: refactor this to inputHandler
    game->soundManager->updateBackgroundMusic(); // Update Music

    aafTitleScreen->update(game->deltaTime);

    //handle input //todo: refactor this to inputHandler

    if (IsKeyPressed(KEY_DOWN))
        selectedOption = (selectedOption + 1) % NUM_OPTIONS;
    if (IsKeyPressed(KEY_UP))
        selectedOption = (selectedOption - 1 + NUM_OPTIONS) % NUM_OPTIONS;

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        if (selectedOption == PLAY)
        {
            // Start the game
            std::cout << "Starting the game..." << std::endl;
            gameAboutToStart = true;
            game->soundManager->playSound("bloodSplatter.mp3");
            aafTitleScreen->setFrameTag("titleScreen-Transition");
        }
        else if (selectedOption == OPTIONS)
        {
            // Handle options (e.g., open options menu)
            std::cout << "Opening options..." << std::endl;
            game->ChangeState(std::make_unique<OptionSelectState>(game));
        }
        else if (selectedOption == EXIT)
        {
            // Exit the game
            std::cout << "Exiting the game..." << std::endl;
            game->quit = true;
        }
    }

    if (gameAboutToStart)

    {
        timerInMs -= game->deltaTime;

        if (timerInMs <= 1.4f && !deadSoundPlayed)
        {
            game->soundManager->playSound("scream.wav");
            game->soundManager->playSound("1bit/manlaughs.wav");
            deadSoundPlayed = true;
        }


        if (timerInMs <= -2.0f)
        {
            game->ChangeState(std::make_unique<CharSelectState>(game));
        }
    }
}

void MenuState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(RAYWHITE);


    // draw stage
    aafTitleScreen->drawCurrentSelectedTag(0, 0);

    // draw options
    if (selectedOption == PLAY)
    {
        DrawText("Play",
                 Constants::RENDERTARGET_WIDTH / 2 - MeasureText("Play", 8) / 2,
                 105,
                 8,
                 Constants::RAYFIGHTER_WHITE);
    }
    else if (selectedOption == OPTIONS)
    {
        DrawText("Options",
                 Constants::RENDERTARGET_WIDTH / 2 - MeasureText("Options", 8) / 2,
                 105,
                 8,
                 Constants::RAYFIGHTER_WHITE);
    }
    else if (selectedOption == EXIT)
    {
        DrawText("Exit",
                 Constants::RENDERTARGET_WIDTH / 2 - MeasureText("Exit", 8) / 2,
                 105,
                 8,
                 Constants::RAYFIGHTER_WHITE);
    }


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


void MenuState::Exit()
{
}
