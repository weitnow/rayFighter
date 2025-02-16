#include "CharSelectState.h"
#include "../Constants.h"
#include "Game.h"
#include "StageSelectState.h"


CharSelectState::CharSelectState(Game* game)
    : BaseState(game), CharSelectScreen(nullptr), selectedCharacterP1{0}, activeCharacterP1{0}, selectedCharacterP2{3},
      activeCharacterP2{3}
{
    CharSelectScreen = game->asepriteManager->getAnimFile("charSelectScreen");
    CharSelectScreen->setFrameTag("charSelectScreen-Idle");

    playerTag = game->asepriteManager->getAnimFile("playerTags");
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
    characters = {{{68, 117, 24, 24}, "Character 1", "gbFighter", 0},
                  {{100, 117, 24, 24}, "Character 2", "nesFighter", 6}, // 5 is the spriteOffsetX
                  {{132, 117, 24, 24}, "Character 3", "gbFighter", 0},
                  {{164, 117, 24, 24}, "Character 4", "nesFighter", 6}}; // 5 is the spriteOffsetX

    // fade in
    screen2DManager->fadeEffect(1.0f, 0.0f);
    //screen2DManager->slideEffect(7.0f, 0);

    // Init of Charactersprites as GameObjects
    p1 = std::make_unique<BaseGameObject>(asepriteManager, p1posX, 68);
    p1->setIsFlippedX(false);
    p1->setCurrentFrameTag(getFrameTagStrOf(1, "Idle")); // playernumber and action
    p1->setDrawShadow(true);
    p1->setShadowGroundLevel(100);
    p1->setShadowColor(Constants::RAYFIGHTER_LIGHTBROWN);
    p1->setShadowOpacity(1.0f);
    p1->setMoveSpeed(50);
    p1->setSpriteOffsetX(characters[activeCharacterP1].spriteOffsetX);
    p1status = {true, false, false, false}; // onOrgPos, outsideScreen, movingIn, movingOut


    p2 = std::make_unique<BaseGameObject>(asepriteManager, 170, 68);
    p2->setIsFlippedX(true);
    p2->setCurrentFrameTag(getFrameTagStrOf(2, "Idle")); // playernumber and action
    p2->setDrawShadow(true);
    p2->setShadowGroundLevel(100);
    p2->setShadowColor(Constants::RAYFIGHTER_LIGHTBROWN);
    p2->setShadowOpacity(1.0f);
    p2->setMoveSpeed(50);
    p2->setSpriteOffsetX(characters[activeCharacterP2].spriteOffsetX);
    p2status = {true, false, false, false}; // onOrgPos, outsideScreen, movingIn, movingOut
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
        DrawSelectionScreen(selectedCharacterP1, 1);
        DrawSelectionScreen(selectedCharacterP2, 2);
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
    std::cout << "CharSelectState::Exit() was called" << std::endl;
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

    CharacterMoveControllerUpdate(1); // Player 1
    CharacterMoveControllerUpdate(2); // Player 2
}

void CharSelectState::DrawPlayers()
{
    p1->draw();
    p2->draw();
}

void CharSelectState::CharacterMoveControllerUpdate(int playerNumber)
{


    int& activeCharacter = (playerNumber == 1) ? activeCharacterP1 : activeCharacterP2;
    int& selectedCharacter = (playerNumber == 1) ? selectedCharacterP1 : selectedCharacterP2;

    BaseGameObject& player = (playerNumber == 1) ? *p1 : *p2;

    auto& status = (playerNumber == 1) ? p1status : p2status;

    bool& onOrgPos = std::get<0>(status);
    bool& outsideScreen = std::get<1>(status);
    bool& movingIn = std::get<2>(status);
    bool& movingOut = std::get<3>(status);


    if (activeCharacter != selectedCharacter)
    {
        // move character off screen
        if (onOrgPos)
        {
            _moveCharacterOffScreen(player);
            onOrgPos = false;
            movingOut = true;
        }
    }
    else // activeCharacter == selectedCharacter
    {
        if (outsideScreen)
        {

            _moveCharacterOnScreen(player);
            outsideScreen = false;
            movingIn = true;
        }
    }

    if (movingOut)
    {
        if (player.getPos().x < -50 || player.getPos().x > 320)
        {
            movingOut = false;
            outsideScreen = true;
            player.setPos(player.getPos().x < -50 ? -50 : 320, player.getPos().y);
            _stopCharacterMovement(player);
            activeCharacter = selectedCharacter;

            // check spriteOffsetX and set it
            if (playerNumber == 1)
            {
                player.setSpriteOffsetX(characters[activeCharacter].spriteOffsetX);
            }
            else
            {
                player.setSpriteOffsetX(characters[activeCharacter].spriteOffsetX);
            }
        }
    }
    else if (movingIn)
    {
        if (playerNumber == 1)
        {
            if (player.getPos().x > p1posX)
            {
                movingIn = false;
                onOrgPos = true;
                _stopCharacterMovement(player);
            }
        }
        else
        {
            if (player.getPos().x < p2posX)
            {
                movingIn = false;
                onOrgPos = true;
                _stopCharacterMovement(player);
            }
        }
    }
}


void CharSelectState::_moveCharacterOffScreen(BaseGameObject& player)
{

    // move player 2 right out of screen
    if (player.getIsFlippedX()) // means = player2
    {
        player.moveRight();
        player.setCurrentFrameTag(getFrameTagStrOf(2, "Walk"));
    }
    else // move player 1 left out of screen
    {
        player.moveLeft();
        player.setCurrentFrameTag(getFrameTagStrOf(1, "Walk"));
    }
}

void CharSelectState::_moveCharacterOnScreen(BaseGameObject& player)
{
    // move player 2 right on of screen
    if (player.getIsFlippedX()) // means = player2
    {
        player.moveLeft();
        player.setCurrentFrameTag(getFrameTagStrOf(2, "Walk"));
    }
    else // move player 1 left out of screen
    {
        player.moveRight();
        player.setCurrentFrameTag(getFrameTagStrOf(1, "Walk"));
    }
}

void CharSelectState::_stopCharacterMovement(BaseGameObject& player)
{
    // move player 2 right on of screen
    if (player.getIsFlippedX()) // means = player2
    {
        player.stop();
        player.setCurrentFrameTag(getFrameTagStrOf(2, "Idle"));
    }
    else // move player 1 left out of screen
    {
        player.stop();
        player.setCurrentFrameTag(getFrameTagStrOf(1, "Idle"));
    }
}

std::string CharSelectState::getFrameTagStrOf(int playerNumber, std::string action)
{
    if (playerNumber == 1)
    {
        return characters[activeCharacterP1].spritename + "-" + action;
    }

    return characters[activeCharacterP2].spritename + "-" + action;
}


void CharSelectState::PauseMusic()
{
    game->soundManager->stopBackgroundMusic();
}

void CharSelectState::ResumeMusic()
{
    game->soundManager->playBackgroundMusic("choices.mp3");
}
