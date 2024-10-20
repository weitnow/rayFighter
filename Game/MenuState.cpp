#include "MenuState.h"
#include "Game.h"


void MenuState::Enter()
{
}

void MenuState::Update()
{
    game->screen2DManager->update(game->deltaTime * Constants::TIME_MULTIPLIER); // update camera
    game->inputHandler->Update();
}

void MenuState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    // BeginTextureMode(target);
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(RAYWHITE);


    // Begin the camera
    BeginMode2D(game->screen2DManager->camera);

    // draw stage
    float stage_scale = 1.f;

    game->background->drawFrame(game->randomBackground, 0, 40, stage_scale, WHITE);


    // End the camera
    EndMode2D();

    // draw gameObjects (player1 and player2 included)
    //game->gameManager->draw();


    game->screen2DManager->endDrawToRenderTarget();
    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToScreen();

    ClearBackground(GREEN);

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

#ifdef DEBUG_WINDOW
    // Draw a black outlined rectangle around the mainView
    DrawRectangleLinesEx(Rectangle{0, 0, 1540, 1070}, 6, BLACK);
    // Draw a second black outlined rectangle on the right side of the screen
    DrawRectangleLinesEx(Rectangle{1545, 0, 374, 1070}, 6, BLACK);
#endif

#ifdef DEBUG_WINDOW
    game->debugInfo->draw();
#endif

    game->screen2DManager->endDrawToScreen();
}


void MenuState::Exit()
{
}
