#include "MenuState.h"
#include "Game.h"
#include "GameState.h"


MenuState::MenuState(Game* game) : BaseState(game), aafTitleScreen(nullptr), gameAboutToStart(false), timerInMs{3.0f}
{
}

MenuState::~MenuState()
{
    //deletion of heap memory is in the exit method
}

void MenuState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->playBackgroundMusic(game->soundManager->killerinstinct_music);
    }
    selectedOption = MenuOptions::PLAY;

    // load TitleScreen
    aafTitleScreen = game->asepriteManager->getAnimFile("titleScreen");
    aafTitleScreen->setFrameTag("titleScreen-Titlescreen");
}

void MenuState::Update()
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
            // Start the game (you would implement game logic here)
            std::cout << "Starting the game..." << std::endl;
            gameAboutToStart = true;
            game->soundManager->playSound(game->soundManager->bloodSplatter);
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
            CloseWindow(); //FIXME: memory leak, implement that game closes properly         }
        }
    }

    aafTitleScreen->update(game->deltaTime);

    if (gameAboutToStart)
    {
        timerInMs -= game->deltaTime;
        if (timerInMs <= 0)
        {
            game->ChangeState(std::make_unique<GameState>(game));
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


    game->screen2DManager->endDrawToRenderTarget();
    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToScreen();

    ClearBackground(GREEN);

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    // Draw Menu
    // Title
    DrawText("Main Menu", Constants::SCREEN_WIDTH / 2 - MeasureText("Main Menu", 40) / 2, 125, 40, BLACK);

    // Menu options
    DrawText("Start Game",
             Constants::SCREEN_WIDTH / 2 - MeasureText("Start Game", 20) / 2,
             200,
             20,
             (selectedOption == PLAY) ? RED : BLACK);
    DrawText("Options",
             Constants::SCREEN_WIDTH / 2 - MeasureText("Options", 20) / 2,
             250,
             20,
             (selectedOption == OPTIONS) ? RED : BLACK);
    DrawText("Exit",
             Constants::SCREEN_WIDTH / 2 - MeasureText("Exit", 20) / 2,
             300,
             20,
             (selectedOption == EXIT) ? RED : BLACK);


    game->screen2DManager->endDrawToScreen();
}


void MenuState::Exit()
{
    delete aafTitleScreen;
    aafTitleScreen = nullptr;
}
