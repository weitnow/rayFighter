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
        game->soundManager->unloadMusic("choices.mp3");
    }


    delete StageSelectScreen;
}

void StageSelectState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("choices.mp3", 1.f);
        game->soundManager->playBackgroundMusic("choices.mp3");
    }

    // Adding stages
    characters = {{{68, 117, 24, 24}, "Character 1"},
                  {{100, 117, 24, 24}, "Character 2"},
                  {{132, 117, 24, 24}, "Character 3"},
                  {{164, 117, 24, 24}, "Character 4"}};
}

void StageSelectState::Update(float deltaTime)
{
    game->soundManager->updateBackgroundMusic(); // Update Music

    //handle input //todo: refactor this to inputHandler
    if (IsKeyPressed(KEY_ENTER))
    {

        game->ChangeState(std::make_unique<GameState>(game));
    }
    if (IsKeyPressed(KEY_D))
    {
        if (selectingCharacter)
        {
            selectedCharacterP1 = (selectedCharacterP1 + 1) % characters.size();
        }
    }
    else if (IsKeyPressed(KEY_A))
    {
        if (selectingCharacter)
        {
            selectedCharacterP1 = (selectedCharacterP1 - 1 + characters.size()) % characters.size();
        }
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        selectingCharacter = !selectingCharacter; // Toggle between character and stage
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        if (selectingCharacter)
        {
            selectedCharacterP2 = (selectedCharacterP2 + 1) % characters.size();
        }
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        if (selectingCharacter)
        {
            selectedCharacterP2 = (selectedCharacterP2 - 1 + characters.size()) % characters.size();
        }
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

    /*
    if (selectingCharacter)
    {
        DrawSelectionScreen(selectedCharacterP1);
    }
    */


    game->screen2DManager->endDrawToRenderTarget();


    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    ClearBackground(GREEN);
    game->screen2DManager->beginDrawToScreen();

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    game->screen2DManager->endDrawToScreen();
}


void StageSelectState::Exit()
{
}

void StageSelectState::DrawSelectionScreen(int selectedIndex)
{
    // Draw

    DrawRectangleLinesEx(characters[selectedIndex].rect, 1.0f, Constants::RAYFIGHTER_WHITE);
}
