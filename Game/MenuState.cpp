#include "MenuState.h"
#include "CharSelectState.h"
#include "Game.h"
#include "OptionState.h"


MenuState::MenuState(Game* game)
    : BaseState(game), aafTitleScreen(nullptr), gameAboutToStart(false), deadSoundPlayed(false),
      optionAboutToStart{false}
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

    // testing //Todo: get rid of this
    screen2DManager->saveScreenResolution();
    screen2DManager->loadScreenResolution();
    screen2DManager->getScreenResolution();
}

void MenuState::Update(float deltaTime)
{
    aafTitleScreen->update(game->deltaTime);

    if (gameAboutToStart)
    {
        timer.Start();

        if (timer.HasElapsed(1.4f))
        {
            screen2DManager->fadeEffect(0.6f, 1.0f);
            //screen2DManager->slideEffect(7.0f, 75);


            if (!deadSoundPlayed)
            {
                game->soundManager->playSound("scream.wav");
                game->soundManager->playSound("1bit/manlaughs.wav");
                deadSoundPlayed = true;
            }
        }

        if (timer.HasElapsed(3.4f))
        {
            //game->ChangeState(std::make_unique<CharSelectState>(game));
            game->PushState(std::make_unique<CharSelectState>(game));
        }
    }

    if (optionAboutToStart)
    {
        timer.Start();
        // fadeout screen
        screen2DManager->fadeEffect(0.6f, 1.0f);

        if (timer.HasElapsed(2.0f))
            game->PushState(std::make_unique<OptionSelectState>(game));
    }

    HandleInput();
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

    screen2DManager->draw();


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

void MenuState::Pause()
{
    PauseMusic();
}

void MenuState::Resume()
{
    gameAboutToStart = false;
    optionAboutToStart = false;
    timer.Reset();
    ResumeMusic();
}


void MenuState::Exit()
{
}

void MenuState::HandleInput()
{
    if (player1Controller->duck && inputHandler->isKeyJustPressed(*player1Controller))
        selectedOption = (selectedOption + 1) % NUM_OPTIONS;
    if (player1Controller->jump && inputHandler->isKeyJustPressed(*player1Controller))
        selectedOption = (selectedOption - 1 + NUM_OPTIONS) % NUM_OPTIONS;

    if (IsKeyPressed(KEY_ENTER) || player1Controller->punch)
    {
        if (selectedOption == PLAY)
        {
            // Start the game
            std::cout << "Starting the game..." << std::endl;
            gameAboutToStart = true;
            if (!deadSoundPlayed)
            {
                game->soundManager->playSound("bloodSplatter.mp3");
            }


            aafTitleScreen->setFrameTag("titleScreen-Transition");
        }
        else if (selectedOption == OPTIONS)
        {
            // Handle options (e.g., open options menu)
            std::cout << "Opening options..." << std::endl;
            optionAboutToStart = true;
        }
        else if (selectedOption == EXIT)
        {
            // Exit the game
            std::cout << "Exiting the game..." << std::endl;
            game->quit = true;
        }
    }
}

void MenuState::PauseMusic()
{
    game->soundManager->stopBackgroundMusic();
}

void MenuState::ResumeMusic()
{

    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->playBackgroundMusic("decisions.mp3");
    }
}
