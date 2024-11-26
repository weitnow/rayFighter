#include "MenuState.h"
#include "CharSelectState.h"
#include "Game.h"


MenuState::MenuState(Game* game)
    : BaseState(game), aafTitleScreen(nullptr), gameAboutToStart(false), timerInMs{3.0f}, deadSoundPlayed(false)
{
}

MenuState::~MenuState()
{
    //deletion of heap memory is in the exit method

    delete aafTitleScreen;
    aafTitleScreen = nullptr;

    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("warriorarrives.mp3");
    }
}

void MenuState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("warriorarrives.mp3", 1.f);
        game->soundManager->playBackgroundMusic("warriorarrives.mp3");
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
        }
        else if (selectedOption == EXIT)
        {
            // Exit the game
            std::cout << "Exiting the game..." << std::endl;
            game->quit = true;
        }
    }

    aafTitleScreen->update(game->deltaTime);

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
        DrawText("1P Start",
                 Constants::RENDERTARGET_WIDTH / 2 - MeasureText("1P Start", 8) / 2,
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

    ClearBackground(GREEN);

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    game->screen2DManager->endDrawToScreen();
}


void MenuState::Exit()
{
}
