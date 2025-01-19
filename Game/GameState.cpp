#include "GameState.h"
#include "../Characters/Fighter1.h"
#include "../Characters/Fighter2.h"
#include "../Constants.h"
#include "../Utils/HelperFunctions.h"
#include "Game.h"


GameState::GameState(Game* game) : BaseState(game)
{
    debugInfo = new DebugInfo(this);        // instance of DebugInfo
    inputHandler->addDebugInfo(*debugInfo); // add debugInfo to inputHandler

    // Create the HUD
    gui = new Gui(game);


    // Create Player 1 and 2
    player1 = new Fighter1(asepriteManager, Constants::PLAYER1_X, Constants::BASELINE);
    player2 = new Fighter2(asepriteManager, Constants::PLAYER2_X, Constants::BASELINE);


    player1->addController(game->inputHandler->getPlayer1Controller());
    player1->init();

    player2->addController(game->inputHandler->getPlayer2Controller());
    player2->init();


    levelAnimFile = asepriteManager->getAnimFile("stages");
    levelAnimFile->setFrameTag("stages-Level");

    if (player1 == nullptr || player2 == nullptr)
    {
        throw std::runtime_error("GameState::GameState -> player1 or player2 is nullptr");
    }
}

GameState::~GameState()
{
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("darkchurch.mp3");
    }

    // Deleting Global Components
    delete debugInfo;

    delete player1;
    delete player2;

    delete gui;

    delete levelAnimFile;
}

void GameState::Enter()
{
    BaseState::Enter();

    // Start playing random background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("darkchurch.mp3", 1.0f);
        game->soundManager->playBackgroundMusic("darkchurch.mp3");
    }
}


void GameState::Update(float deltaTime)
{
    _updateIsLeftPlayer1and2(); // Check if player1 is left of player2

    _checkHitsBetweenPlayers(); // Check if player1 and player2 are hitting each other

    // Update all gameObjects
    for (auto& object : gameObjects)
    {
        object->update(deltaTime);
    }

    // Update all baseCharacters
    for (auto& object : baseCharacters)
    {
        object->update(deltaTime);
    }

    // Update players
    player1->update(deltaTime); // _keepOnStage() is called in player update
    player2->update(deltaTime); // _keepOnStage() is called in player update

    _checkCollisionsBetweenPlayers();

    _updateMiddlePointBetweenPlayers(); // (needs to be done befor _updateCamera)

    _updateCamera(true); //true = camera has restrictions turned on

    _keepPlayersOnStage(); // Keep the players on the stage

    // update levelAnimFile
    levelAnimFile->update(deltaTime);

    // Update the HUD
    gui->update(deltaTime);

    HandleInput();
}

void GameState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    // BeginTextureMode(target);
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(WHITE);

    // DRAW STATIONARY BACKGROUND
    levelAnimFile->drawFrame("stages-Background", -Constants::CAM_MIDDLE, 24, 1, WHITE);

    // Begin the camera
    BeginMode2D(game->screen2DManager->camera);

    // DRAW LEVEL
    levelAnimFile->drawCurrentSelectedTag(0, 24, 1, WHITE);

    // draw gameObjects (player1 and player2 included)
    // Draw all gameObjects
    for (auto& object : gameObjects)
    {
        object->draw();
    }

    // Draw all baseSpriteObjects
    for (auto& object : baseSpriteObjects)
    {
        object->draw();
    }

    // Draw all baseCharacters
    for (auto& object : baseCharacters)
    {
        object->draw();
    }

    // draw player 1 and 2
    player1->draw();
    player2->draw();

    if (Global::debugMode)
    {
        // Draw the middlePointXbetweenPlayers
        DrawLine(middlePointXbetweenPlayers, 0, middlePointXbetweenPlayers, 300, RED);

        // Draw the middlePointYbetweenPlayers
        DrawLine(0, middlePointYbetweenPlayers, Constants::STAGE_WIDTH, middlePointYbetweenPlayers, RED);
    }


    // End the camera
    EndMode2D();

    // Draw the screenEffects
    screen2DManager->draw();

    // Draw the GUI
    gui->draw();


    game->screen2DManager->endDrawToRenderTarget();
    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToScreen();

    ClearBackground(BLACK);

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    if (Global::debugWindow)
    {
        // Draw a black outlined rectangle around the mainView
        DrawRectangleLinesEx(Rectangle{0, 0, 1540, 1070}, 6, BLACK);
        // Draw a second black outlined rectangle on the right side of the screen
        DrawRectangleLinesEx(Rectangle{1545, 0, 374, 1070}, 6, BLACK);

        debugInfo->draw();
    }

    // render overlay only if not in debug mode
    if (!Global::debugMode)
    {
        game->screen2DManager->drawOverlay();
    }

    game->screen2DManager->endDrawToScreen();
}

void GameState::Pause()
{
}

void GameState::Resume()
{
}

void GameState::Exit()
{
}

void GameState::HandleInput()
{
    // debug mode
    if (player1Controller->key_q)
    {
        Global::debugMode = !Global::debugMode;
        debugInfo->setDebugMode(Global::debugMode);
    }

    // TODO: remove this
    if (IsKeyPressed(KEY_Z)) //Z = Y because Swiss Keyboard
    {
        soundManager->playSound("earthquake.wav");
        screen2DManager->setScreenGenericEffects("screenEffects-Leafs", 1);
        game->screen2DManager->startScreenShake(0.7f, 0.5f);
    }

    // check if ESC key is pressed or windows close button is clicked
    if (player1Controller->key_enter)
    {
        //pop this state and return to menu
        game->PopState();
    }
}

Vector2 GameState::getMiddlePointBetweenPlayers() const
{
    return Vector2{static_cast<float>(middlePointXbetweenPlayers), static_cast<float>(middlePointYbetweenPlayers)};
}


int GameState::_getScreenPosXofObject(BaseGameObject& object)
{
    return object.getPos().x - cameraX;
}

void GameState::_updateMiddlePointBetweenPlayers()
{
    middlePointXbetweenPlayers = (player1->getPos().x + player2->getPos().x + 32) / 2.f;
    middlePointYbetweenPlayers = (player1->getPos().y + player2->getPos().y) / 2.f + Constants::PLAYER_PIXELSIZE / 2;
}

void GameState::_updateIsLeftPlayer1and2()
{
    // check wheter player 1 is left of player 2
    if (player1->getPos().x < player2->getPos().x)
    {
        player1->setIsLeft(true);
        player2->setIsLeft(false);
    }
    else
    {
        player1->setIsLeft(false);
        player2->setIsLeft(true);
    }
}

void GameState::_checkCollisionsBetweenPlayers()
{
    // Check if player1 and player2 are colliding
    // TODO: get rid of hardcoded [0]
    CollisionBox2D player1PushBox = player1->getPushBoxes()[0];
    CollisionBox2D player2PushBox = player2->getPushBoxes()[0];

    if (Utils::checkCollision(player1PushBox, player2PushBox))
    {
        // Handle collision (you can define specific collision logic here)
        if (player1->getIsLeft())
        {
            player1->setPushVector({-50, 0});
            player2->setPushVector({50, 0});
        }
        else
        {
            player1->setPushVector({50, 0});
            player2->setPushVector({-50, 0});
        }
    }
}

void GameState::_checkHitsBetweenPlayers()
{
    // TODO: refactor this, this stuff must be in the statemachine
    // loop through all hitboxes of player1
    for (auto& hitbox : player1->getHitBoxes())
    {
        // loop through all hurtboxes of player2
        for (auto& hurtbox : player2->getHurtBoxes())
        {
            if (Utils::checkCollision(hitbox, hurtbox) && player1->canDealDamage)
            {
                // Handle hit (you can define specific hit logic here)
                player2->takeDamage(1, &hitbox);
                if (player1->getCurrentState() == "Kick")
                {
                    player2->setPushVector({200, 0});
                }
                else if (player1->getCurrentState() == "Punch")
                {
                    player2->setPushVector({120, 0});
                }

                player1->canDealDamage = false;
            }
        }
    }

    // loop through all hitboxes of player2
    for (auto& hitbox : player2->getHitBoxes())
    {
        // loop through all hurtboxes of player1
        for (auto& hurtbox : player1->getHurtBoxes())
        {
            if (Utils::checkCollision(hitbox, hurtbox) && player2->canDealDamage)
            {
                // Handle hit (you can define specific hit logic here)
                player1->takeDamage(1, &hitbox);
                player2->canDealDamage = false;
            }
        }
    }
}

void GameState::_keepPlayersOnStage()
{
    // KEEP THE CHARACTER ON THE STAGE (only X Direction)
    // check if the character is out of bounds
    if (player1->getPos().x < 0)
    {
        // keep player on screen
        player1->setPos(0, player1->getPos().y);
    }
    else if (player1->getPos().x > Constants::STAGE_WIDTH - Constants::PLAYER_PIXELSIZE)
    {
        // keep player on screen
        player1->setPos(Constants::STAGE_WIDTH - Constants::PLAYER_PIXELSIZE, player1->getPos().y);
    }

    // check if the character is out of bounds
    if (player2->getPos().x < 0)
    {
        // keep player on screen
        player2->setPos(0, player2->getPos().y);
    }
    else if (player2->getPos().x > Constants::STAGE_WIDTH - Constants::PLAYER_PIXELSIZE)
    {
        // keep player on screen
        player2->setPos(Constants::STAGE_WIDTH - Constants::PLAYER_PIXELSIZE, player2->getPos().y);
    }
}

void GameState::_updateCamera(bool restriction)
{
    cameraX = middlePointXbetweenPlayers - (Constants::RENDERTARGET_WIDTH / 2);

    // calculate y position of the camera
    cameraY = 0 - (28 - middlePointYbetweenPlayers / 4);

    // ensures that the camera doenst go to high in Y direction
    if (restriction)
    {
        // make sure the camera doesn't go too high if players are jumping
        if (cameraY < -7)
        {
            cameraY = -7;
        }

        // restrict the camera to the stage
        if (cameraX < Constants::CAM_MOST_LEFT) // if the camera is at the most left of the stage, which is 0
        {
            cameraX = Constants::CAM_MOST_LEFT;
        }
        else if (cameraX > Constants::CAM_MOST_RIGHT) // if the camera is at the most right of the stage, which is 160
        {
            cameraX = Constants::CAM_MOST_RIGHT;
        }
    }

    // update y position of the camera
    game->screen2DManager->camera.target.y = cameraY;

    // update x position of the camera
    game->screen2DManager->camera.target.x = cameraX;
}
