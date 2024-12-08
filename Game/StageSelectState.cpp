#include "StageSelectState.h"
#include "../Constants.h"
#include "Game.h"
#include "GameState.h"


StageSelectState::StageSelectState(Game* game) : BaseState(game), StageSelectScreen(nullptr)
{
    StageSelectScreen = game->asepriteManager->getAnimFile("stageSelectScreen");
    StageSelectScreen->setFrameTag("stageSelectScreen-Idle");
}

StageSelectState::~StageSelectState()
{

    std::cout << "CharSelectState Destructor called, unloading resources" << std::endl;

    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("sunburn.mp3");
    }


    delete StageSelectScreen;
}

void StageSelectState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("sunburn.mp3", 1.f);
        game->soundManager->playBackgroundMusic("sunburn.mp3");
    }

    // Adding stages
    stages = {{{68, 117, 24, 24}, "Stage 1"},
              {{100, 117, 24, 24}, "Stage 2"},
              {{132, 117, 24, 24}, "Stage 3"},
              {{164, 117, 24, 24}, "Stage 4"}};
}

void StageSelectState::Update(float deltaTime)
{
    game->soundManager->updateBackgroundMusic(); // Update Music

    // Update StageSelectScreen
    StageSelectScreen->update(deltaTime);

    //handle input //todo: refactor this to inputHandler
    if (IsKeyPressed(KEY_ENTER))
    {

        game->ChangeState(std::make_unique<GameState>(game));
    }
    if (IsKeyPressed(KEY_D))
    {
        if (selectingCharacter)
        {
            selectedStage = (selectedStage + 1) % stages.size();
        }
    }
    else if (IsKeyPressed(KEY_A))
    {
        if (selectingCharacter)
        {
            selectedStage = (selectedStage - 1 + stages.size()) % stages.size();
        }
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        selectingCharacter = !selectingCharacter; // Toggle between character and stage
    }
}

void StageSelectState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(GREEN);

    // Draw StageSelectScreen
    StageSelectScreen->drawCurrentSelectedTag(0, 0);

    DrawSelectionScreen(selectedStage);


    game->screen2DManager->endDrawToRenderTarget();


    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    ClearBackground(Constants::RAYFIGHTER_LIGHTROSA);
    game->screen2DManager->beginDrawToScreen();

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    // render overlay
    game->screen2DManager->drawOverlay();

    game->screen2DManager->endDrawToScreen();
}


void StageSelectState::Exit()
{
}

void StageSelectState::DrawSelectionScreen(int selectedIndex)
{
    // Draw

    DrawRectangleLinesEx(stages[selectedIndex].rect, 1.0f, Constants::RAYFIGHTER_WHITE);
}
