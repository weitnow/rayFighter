#include "CharSelectState.h"
#include "../Constants.h"
#include "Game.h"
#include "StageSelectState.h"
#include <stdexcept> // Include for std::invalid_argument


CharSelectState::CharSelectState(Game* game)
    : BaseState(game), CharSelectScreen(nullptr), currentSelectedCharacterP1{0}, previousSelectedCharacterP1{0},
      currentSelectedCharacterP2{3}, previousSelectedCharacterP2{3}
{
    CharSelectScreen = game->asepriteManager->getAnimFile("charSelectScreen");
    CharSelectScreen->setFrameTag("charSelectScreen-Idle");

    playerTag = game->asepriteManager->getAnimFile("playerTags");

    // Init of Charactersprites as GameObjects
    p1 = std::make_unique<BaseGameObject>(asepriteManager, 45, 68);
    p1->setDrawShadow(true);
    p1->setShadowGroundLevel(100);
    p1->setShadowColor(Constants::RAYFIGHTER_LIGHTBROWN);
    p1->setShadowOpacity(1.0f);


    p2 = std::make_unique<BaseGameObject>(asepriteManager, 170, 68);
    p2->setIsFlippedX(true);
    p2->setCurrentFrameTag("nesFighter-Idle");
    p2->setDrawShadow(true);
    p2->setShadowGroundLevel(100);
    p2->setShadowColor(Constants::RAYFIGHTER_LIGHTBROWN);
    p2->setShadowOpacity(1.0f);
}

CharSelectState::~CharSelectState()
{

    std::cout << "CharSelectState Destructor called, unloading resources" << std::endl;

    game->soundManager->unloadMusic("choices.mp3");


    delete CharSelectScreen;
    delete playerTag;
}

void CharSelectState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    game->soundManager->loadMusic("choices.mp3", 1.f);
    game->soundManager->playBackgroundMusic("choices.mp3");


    // Adding characters
    characters = {{{68, 117, 24, 24}, "Character 1"},
                  {{100, 117, 24, 24}, "Character 2"},
                  {{132, 117, 24, 24}, "Character 3"},
                  {{164, 117, 24, 24}, "Character 4"}};

    // fade in
    screen2DManager->fadeEffect(1.0f, 0.0f);
    //screen2DManager->slideEffect(7.0f, 0);
}

void CharSelectState::Update(float deltaTime)
{
    // Update CharSelectScreen
    CharSelectScreen->update(deltaTime);

    if (CharSelectScreen->getCurrentFrame() == 4 || CharSelectScreen->getCurrentFrame() == 12)
    {
        SoundManager::getInstance().playSound("thunder.wav");
    }

    UpdatePlayers(deltaTime);

    HandleInput();
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
        DrawSelectionScreen(currentSelectedCharacterP1, 1);
        DrawSelectionScreen(currentSelectedCharacterP2, 2);
    }

    DrawPlayers();

    screen2DManager->draw();
    game->screen2DManager->endDrawToRenderTarget();


    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    ClearBackground(BLACK);
    game->screen2DManager->beginDrawToScreen();

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    // render overlay
    game->screen2DManager->drawOverlay();

    game->screen2DManager->endDrawToScreen();
}

void CharSelectState::Pause()
{
    PauseMusic();
}

void CharSelectState::Resume()
{
    ResumeMusic();
}


void CharSelectState::Exit()
{
}

void CharSelectState::HandleInput()
{

    if (player1Controller->kick)
    {
        //pop this state and return to menu
        game->PopState();
    }

    if (IsKeyPressed(KEY_ENTER) || player1Controller->punch)
    {
        game->ChangeState(std::make_unique<StageSelectState>(game));
    }
    if (IsKeyPressed(KEY_D))
    {
        if (selectingCharacter)
        {
            previousSelectedCharacterP1 = currentSelectedCharacterP1;
            currentSelectedCharacterP1 = (currentSelectedCharacterP1 + 1) % characters.size();
            changePlayerCharacter(1);
        }
    }
    else if (IsKeyPressed(KEY_A))
    {
        if (selectingCharacter)
        {
            previousSelectedCharacterP1 = currentSelectedCharacterP1;
            currentSelectedCharacterP1 = (currentSelectedCharacterP1 - 1 + characters.size()) % characters.size();
            changePlayerCharacter(1);
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
            previousSelectedCharacterP2 = currentSelectedCharacterP2;
            currentSelectedCharacterP2 = (currentSelectedCharacterP2 + 1) % characters.size();
            changePlayerCharacter(2);
        }
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        if (selectingCharacter)
        {
            previousSelectedCharacterP2 = currentSelectedCharacterP2;
            currentSelectedCharacterP2 = (currentSelectedCharacterP2 - 1 + characters.size()) % characters.size();
            changePlayerCharacter(2);
        }
    }
}

void CharSelectState::DrawSelectionScreen(int selectedIndex, int playerNumber)
{
    // Draw
    DrawRectangleLinesEx(characters[selectedIndex].rect, 1.0f, Constants::RAYFIGHTER_WHITE);

    if (playerNumber == 1)
    {
        // Draw player tag
        playerTag->drawFrame("playerTags-P1", characters[selectedIndex].rect.x, 110, 1, WHITE);

        // Draw player name
        DrawText((characters[selectedIndex].name).c_str(), 10, 10, 8, WHITE);
    }
    else
    {
        // Draw player tag
        playerTag->drawFrame("playerTags-P2", characters[selectedIndex].rect.x + 12, 110, 1, WHITE);

        // Draw player name
        DrawText((characters[selectedIndex].name).c_str(), 182, 10, 8, WHITE);
    }
}

void CharSelectState::UpdatePlayers(float deltaTime)
{
    p1->update(deltaTime);
    p2->update(deltaTime);
}

void CharSelectState::DrawPlayers()
{
    p1->draw();
    p2->draw();
}

void CharSelectState::changePlayerCharacter(int playerNumber)
{
    if (playerNumber == 1)
    {
        // Player 1

        if (currentSelectedCharacterP1 == 0) // Character 0
            p1->setCurrentFrameTag("nesFighter-Idle");

        else if (currentSelectedCharacterP1 == 1) // Character 1
            p1->setCurrentFrameTag("gbFighter-Idle");

        else if (currentSelectedCharacterP1 == 2) // Character 2
            p1->setCurrentFrameTag("gbFighter-Idle");

        else if (currentSelectedCharacterP1 == 3) // Character 3
            p1->setCurrentFrameTag("gbFighter-Idle");
    }
    else if (playerNumber == 2)
    {
        // Player 2
        if (currentSelectedCharacterP2 == 0) // Character 0
            p2->setCurrentFrameTag("nesFighter-Idle");

        else if (currentSelectedCharacterP2 == 1) // Character 1
            p2->setCurrentFrameTag("gbFighter-Idle");

        else if (currentSelectedCharacterP2 == 2) // Character 2
            p2->setCurrentFrameTag("gbFighter-Idle");

        else if (currentSelectedCharacterP2 == 3) // Character 3
            p2->setCurrentFrameTag("gbFighter-Idle");
    }
    else
    {
        throw std::invalid_argument("Invalid parameter: Must be 1 or 2.");
    }
}

void CharSelectState::PauseMusic()
{
    game->soundManager->stopBackgroundMusic();
}

void CharSelectState::ResumeMusic()
{
    game->soundManager->playBackgroundMusic("choices.mp3");
}
