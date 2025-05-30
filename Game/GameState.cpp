#include "GameState.h"
#include "../Characters/Fighter1.h"
#include "../Characters/Fighter2.h"
#include "../Characters/Fighter3.h"
#include "../Constants.h"
#include "../Utils/HelperFunctions.h"
#include "Game.h"

GameState::GameState(Game* game) : BaseState(game)
{
    debugInfo = new DebugInfo(this);        // instance of DebugInfo
    inputHandler->addDebugInfo(*debugInfo); // add debugInfo to inputHandler

    // Create Player 1 and 2
    //player1 = createPlayer(game->player1, 1);
    player1 = createPlayer(1, 1);

    //player2 = createPlayer(game->player2, 2); //Todo: replace by this code
    player2 = createPlayer(2, 2);

    // Set the opponent for each player
    player1->getStatemachine().setOpponent(player2);
    player2->getStatemachine().setOpponent(player1);

    // Create the HUD
    gui = new Gui(game);
    gui->init(this);

    levelAnimFile = asepriteManager->getAnimFile("stages");
    levelAnimFile->setFrameTag("stages-Level");

    if (player1 == nullptr || player2 == nullptr)
    {
        throw std::runtime_error("GameState::GameState -> player1 or player2 is nullptr");
    }
}

GameState::~GameState()
{
    game->soundManager->unloadMusic("darkchurch.mp3");

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
    game->soundManager->loadMusic("darkchurch.mp3", 1.0f);
    game->soundManager->playBackgroundMusic("darkchurch.mp3");

    // Todo: get rid of this
    gui->setWinningPoint1(1);
    gui->setWinningPoint2(1);
}

void GameState::Update(float deltaTime)
{
    _updateIsLeftPlayer1and2(); // Check if player1 is left of player2


    // Update all gameObjects
    _updateAllGameObjects(deltaTime);
    // Update all baseCharacters
    _updateAllBaseCharacters(deltaTime);


    // Update players
    player1->update(deltaTime);
    player2->update(deltaTime);

    _checkPushCollisionsBetweenPlayers();

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

BaseCharacter* GameState::createPlayer(int characterNumber, int playerNumber)
{

    BaseCharacter* player = nullptr;
    int Xpos = (playerNumber == 1) ? Constants::PLAYER1_X : Constants::PLAYER2_X;

    switch (characterNumber)
    {
    case 1:
        player = new Fighter1(asepriteManager, Xpos, Constants::BASELINE);
        break;
    case 2:
        player = new Fighter2(asepriteManager, Xpos, Constants::BASELINE);
        break;
    case 3:
        player = new Fighter3(asepriteManager, Xpos, Constants::BASELINE);
        break;
    default:
        player = new Fighter1(asepriteManager, Xpos, Constants::BASELINE);
        break;
    }

    if (playerNumber == 1)
    {
        player->addController(game->inputHandler->getPlayer1Controller());
        player->setPlayerNumber(1);
    }
    else if (playerNumber == 2)
    {
        player->addController(game->inputHandler->getPlayer2Controller());
        player->setPlayerNumber(2);
    }


    player->init(); // initialize the player
    player->getStatemachine().setGameState(this);
    player->setGameState(this); // set the game state for the player

    player->setPlayerNumber(playerNumber);

    //add playerPtr to InputHandler
    game->inputHandler->addPlayer(player, playerNumber);

    return player;
}

void GameState::addGameObject(unique<BaseGameObject> gameObject)
{
    if (gameObject == nullptr)
    {
        throw std::runtime_error("GameState::addGameObject -> gameObject is nullptr");
    }

    // set the game state for the gameObject
    gameObject->setGameState(this);

    // add the gameObject to the list
    gameObjects.push_back(std::move(gameObject));

    // if the gameObject is a BaseCharacter, add it to the baseCharacters list
    if (auto* character = dynamic_cast<BaseCharacter*>(gameObjects.back().get()))
    {
        // Release ownership from gameObjects and transfer to baseCharacters
        std::unique_ptr<BaseGameObject> basePtr = std::move(gameObjects.back());
        gameObjects.pop_back();
        std::unique_ptr<BaseCharacter> charPtr(static_cast<BaseCharacter*>(basePtr.release()));
        baseCharacters.push_back(std::move(charPtr));
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

void GameState::_checkPushCollisionsBetweenPlayers()
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

void GameState::_updateAllGameObjects(float deltaTime)
{
    for (auto& object : gameObjects)
    {
        object->update(deltaTime);
    }
}

void GameState::_updateAllBaseCharacters(float deltaTime)
{
    for (auto& object : baseCharacters)
    {
        object->update(deltaTime);
    }
}
