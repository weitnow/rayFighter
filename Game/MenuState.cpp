#include "MenuState.h"
#include "Game.h"
#include "GameState.h"


void MenuState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->playBackgroundMusic(game->soundManager->killerinstinct_music);
    }

    selectedOption = MenuOptions::PLAY;
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
            game->ChangeState(std::make_unique<GameState>(game)); //FIXME: this is a memory leak
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
    float stage_scale = 1.f;

    game->background->drawFrame(game->randomBackground, 0, 40, stage_scale, WHITE);


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
    DrawText("Main Menu", Constants::SCREEN_WIDTH / 2 - MeasureText("Main Menu", 40) / 2, 100, 40, BLACK);

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
}
