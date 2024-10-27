#include "GameState.h"
#include "Game.h"

// Todo: get rid of his, only used for testing
#include "../Utils/HelperFunctions.h"

void GameState::Enter()
{
    BaseState::Enter();

    // Start playing random background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->playRandomBackgroundMusic();
    }
}

void GameState::Update()
{
    game->inputHandler->Update(); // Handle Input

    game->gameManager->update(game->deltaTime *
                              Constants::TIME_MULTIPLIER); // Update gameObjects (player1 and player2 included)
    game->soundManager->updateBackgroundMusic();           // Update Music}
}

void GameState::Render()
{

    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    // BeginTextureMode(target);
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(RAYWHITE);


    // calculate Camera
    float& middlepointX = game->gameManager->middlePointXbetweenPlayers;

    if (middlepointX < 105.f)
    {
        game->camPos = game->camPos - 50 * game->deltaTime;
        game->player1->setCamVector(Vector2{50.f, 0.f});
        game->player2->setCamVector(Vector2{50.f, 0.f});
    }
    else if (middlepointX > 152.f)
    {
        // move background to the left
        game->camPos = game->camPos + 50 * game->deltaTime;
        game->player1->setCamVector(Vector2{-50.f, 0.f});
        game->player2->setCamVector(Vector2{-50.f, 0.f});
    }
    else
    {
        // don't move anything
        game->player1->resetCamVector();
        game->player2->resetCamVector();
    }

    game->screen2DManager->camera.target.x = game->camPos;


    // Begin the camera
    BeginMode2D(game->screen2DManager->camera);

    // draw stage
    float stage_scale = 1.f;

    game->background->drawFrame(game->randomBackground, 0 - Constants::BACKGROUND_WIDTH, 40, stage_scale, WHITE);
    game->background->drawFrame(game->randomBackground, 0, 40, stage_scale, WHITE);
    game->background->drawFrame(game->randomBackground, 0 + Constants::BACKGROUND_WIDTH, 40, stage_scale, WHITE);

    // End the camera
    EndMode2D();

    // draw gameObjects (player1 and player2 included)
    game->gameManager->draw();


    game->screen2DManager->endDrawToRenderTarget();
    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToScreen();

    ClearBackground(GREEN);

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    if (Global::debugWindow)
    {
        // Draw a black outlined rectangle around the mainView
        DrawRectangleLinesEx(Rectangle{0, 0, 1540, 1070}, 6, BLACK);
        // Draw a second black outlined rectangle on the right side of the screen
        DrawRectangleLinesEx(Rectangle{1545, 0, 374, 1070}, 6, BLACK);

        game->debugInfo->draw();
    }
    game->screen2DManager->endDrawToScreen();
}

void GameState::Exit()
{
    // Cleanup for game scene
}
