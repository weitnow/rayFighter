#include "CharSelectState.h"
#include "../Constants.h"
#include "Game.h"
#include "StageSelectState.h"


CharSelectState::CharSelectState(Game* game) : BaseState(game), CharSelectScreen(nullptr)
{
    CharSelectScreen = game->asepriteManager->getAnimFile("charSelectScreen");
    CharSelectScreen->setFrameTag("charSelectScreen-Idle");


    playerTag = game->asepriteManager->getAnimFile("playerTags");
}

CharSelectState::~CharSelectState()
{

    std::cout << "CharSelectState Destructor called, unloading resources" << std::endl;

    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("choices.mp3");
    }


    delete CharSelectScreen;
    delete playerTag;
}

void CharSelectState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("choices.mp3", 1.f);
        game->soundManager->playBackgroundMusic("choices.mp3");
    }

    // Adding characters
    characters = {{{68, 117, 24, 24}, "Character 1"},
                  {{100, 117, 24, 24}, "Character 2"},
                  {{132, 117, 24, 24}, "Character 3"},
                  {{164, 117, 24, 24}, "Character 4"}};
}

void CharSelectState::Update(float deltaTime)
{
    game->soundManager->updateBackgroundMusic(); // Update Music

    // Update CharSelectScreen
    CharSelectScreen->update(deltaTime);

    //handle input //todo: refactor this to inputHandler
    if (IsKeyPressed(KEY_ENTER))
    {

        game->ChangeState(std::make_unique<StageSelectState>(game));
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


    if (CharSelectScreen->getCurrentFrame() == 4 || CharSelectScreen->getCurrentFrame() == 12)
    {
        SoundManager::getInstance().playSound("thunder.wav");
    }
}

void CharSelectState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(GREEN);

    // Draw CharSelectScreen
    CharSelectScreen->drawCurrentSelectedTag(0, 0);

    if (selectingCharacter)
    {
        DrawSelectionScreen(selectedCharacterP1, 1);
        DrawSelectionScreen(selectedCharacterP2, 2);
    }


    game->screen2DManager->endDrawToRenderTarget();


    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    ClearBackground(Constants::RAYFIGHTER_LIGHTROSA);
    game->screen2DManager->beginDrawToScreen();

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    game->screen2DManager->endDrawToScreen();
}


void CharSelectState::Exit()
{
}

void CharSelectState::DrawSelectionScreen(int selectedIndex, int playerNumber)
{
    // Draw

    DrawRectangleLinesEx(characters[selectedIndex].rect, 1.0f, Constants::RAYFIGHTER_WHITE);

    // Draw player tag
    if (playerNumber == 1)
    {
        playerTag->drawFrame("playerTags-P1", characters[selectedIndex].rect.x, 110, 1, WHITE);
    }
    else
    {
        playerTag->drawFrame("playerTags-P2", characters[selectedIndex].rect.x + 12, 110, 1, WHITE);
    }
}
