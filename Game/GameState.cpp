#include "GameState.h"
#include "../Characters/Fighter1.h"
#include "../Characters/Fighter2.h"
#include "../Characters/Fighter3.h"
#include "../Constants.h"
#include "../Systems/CollisionDetection.h"
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

    hitDetection = &CollisionDetection::getInstance(); // get reference to singleton
    hitDetection->init(this); // pass gamestate to singleton to access gameobjects for hitdetection

    inputHandler->takeReferenceToGameState(this); // inputhandler needs access to Gamestate to calculate if PlayerShouldBlock

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

    // Update players
    player1->update(deltaTime);
    player2->update(deltaTime);

    _checkPushCollisionsBetweenPlayers();

    _updateMiddlePointBetweenPlayers(); // (needs to be done befor _updateCamera)

    _updateCamera(true); //true = camera has restrictions turned on

    _keepPlayersOnStage(); // Keep the players on the stage

    _updateAllGameObjects(deltaTime);
    _updateAllBaseCharacters(deltaTime);

    // update levelAnimFile
    levelAnimFile->update(deltaTime);

    // Update the HUD
    gui->update(deltaTime);

    // Hitdetection
    _updateHitDetection();

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

    _drawAllBaseCharacters();
    _drawAllGameObjects();

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


void GameState::addGameObject(std::shared_ptr<BaseGameObject> gameObject, int ownerPlayerNumber)
{
    if (!gameObject)
    {
        throw std::runtime_error("GameState::addGameObject -> gameObject is nullptr");
    }

    gameObject->setGameState(this);

    if (auto character = std::dynamic_pointer_cast<BaseCharacter>(gameObject))
    {
        baseCharacters.push_back(character);

        // Assign weak reference to appropriate baseCharacters* vector
        switch (ownerPlayerNumber)
        {
        case 1:
            baseCharactersP1.push_back(character);
            break;
        case 2:
            baseCharactersP2.push_back(character);
            break;
        case -1:
            baseCharactersNoOwner.push_back(character);
            break;
        case -2:
            baseCharactersBothOwner.push_back(character);
            break;
        default:
            throw std::runtime_error("GameState::addGameObject -> Invalid ownerPlayerNumber for BaseCharacter");
        }
    }
    else
    {
        gameObjects.push_back(gameObject);

        // Assign weak reference to appropriate gameObjects* vector
        switch (ownerPlayerNumber)
        {
        case 1:
            gameObjectsP1.push_back(gameObject);
            break;
        case 2:
            gameObjectsP2.push_back(gameObject);
            break;
        case -1:
            gameObjectsNoOwner.push_back(gameObject);
            break;
        case -2:
            gameObjectsBothOwner.push_back(gameObject);
            break;
        default:
            throw std::runtime_error("GameState::addGameObject -> Invalid ownerPlayerNumber for BaseGameObject");
        }
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
    // check whether player 1 is left of player 2
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
    for (int i = static_cast<int>(gameObjects.size()) - 1; i >= 0; --i)
    {
        if (gameObjects[i]->getShouldDestroy())
        {
            auto destroyedPtr = gameObjects[i];
            gameObjects.erase(gameObjects.begin() + i);

            // Clean up weak references that point to this destroyed object
            auto removeDestroyedWeakRefs = [&](std::vector<std::weak_ptr<BaseGameObject>>& vec)
            {
                vec.erase(std::remove_if(vec.begin(), vec.end(),
                    [&](const std::weak_ptr<BaseGameObject>& weakRef)
                    {
                        auto shared = weakRef.lock();
                        return !shared || shared == destroyedPtr;
                    }), vec.end());
            };

            removeDestroyedWeakRefs(gameObjectsP1);
            removeDestroyedWeakRefs(gameObjectsP2);
            removeDestroyedWeakRefs(gameObjectsNoOwner);
            removeDestroyedWeakRefs(gameObjectsBothOwner);
        }
        else
        {
            gameObjects[i]->update(deltaTime);
        }
    }
}


void GameState::_updateAllBaseCharacters(float deltaTime)
{
    for (int i = static_cast<int>(baseCharacters.size()) - 1; i >= 0; --i)
    {
        if (baseCharacters[i]->getShouldDestroy())
        {
            auto destroyedPtr = baseCharacters[i];
            baseCharacters.erase(baseCharacters.begin() + i);

            // Remove from all weak character lists
            auto removeDestroyedWeakRefs = [&](std::vector<std::weak_ptr<BaseCharacter>>& vec) {
                vec.erase(std::remove_if(vec.begin(),
                                         vec.end(),
                                         [&](const std::weak_ptr<BaseCharacter>& weakRef) {
                                             auto shared = weakRef.lock();
                                             return !shared || shared == destroyedPtr;
                                         }),
                          vec.end());
            };

            removeDestroyedWeakRefs(baseCharactersP1);
            removeDestroyedWeakRefs(baseCharactersP2);
            removeDestroyedWeakRefs(baseCharactersNoOwner);
            removeDestroyedWeakRefs(baseCharactersBothOwner);
        }
        else
        {
            baseCharacters[i]->update(deltaTime);
        }
    }
}
void GameState::_updateHitDetection()
{
    // Hitdetection
    hitDetection->checkForCollision(*player1, *player2); // check for collision between player1 and player2

    hitDetection->checkForCollision(*player1, gameObjectsP2); // check for collision between player1 and gameObjectsP2
    //hitDetection->checkForCollision(*player1, gameObjectsNoOwner); // check for collision between player1 and gameObjectsNoOwner
    //hitDetection->checkForCollision(*player1, gameObjectsBothOwner); // check for collision between player1 and gameObjectsBothOwner
    hitDetection->checkForCollision(*player1, baseCharactersP1); // check for collision between player1 and baseCharactersP1
    //hitDetection->checkForCollision(*player1, baseCharactersNoOwner); // check for collision between player1 and baseCharactersNoOwner
    //hitDetection->checkForCollision(*player1, baseCharactersBothOwner); // check for collision between player1 and baseCharactersBothOwner

    hitDetection->checkForCollision(*player2, gameObjectsP1);
    //hitDetection->checkForCollision(*player2, gameObjectsNoOwner);
    //hitDetection->checkForCollision(*player2, gameObjectsBothOwner);
    hitDetection->checkForCollision(*player2, baseCharactersP2);
    //hitDetection->checkForCollision(*player2, baseCharactersNoOwner);
    //hitDetection->checkForCollision(*player2, baseCharactersBothOwner);
}

void GameState::_drawAllGameObjects()
{
    for (auto& object : gameObjects)
    {
        object->draw();
    }
}
void GameState::_drawAllBaseCharacters()
{
    // Draw all baseCharacters
    for (auto& object : baseCharacters)
    {
        object->draw();
    }
}
float GameState::distanceBetweenGameObjects(BaseGameObject* object1, BaseGameObject* object2)
{
    return Utils::calculateDistance(*object1, *object2);
}
BaseGameObject* GameState::getClosestEnemyOf(BaseGameObject& baseGameObject,
                                             float* outDistance,
                                             std::vector<BaseGameObject*>* outEnemies)
{
    float distanceClosestEnemy = 500.0f;
    BaseGameObject* closestEnemy = nullptr;

    // clear outEnemies vector, so that is is empty
    if (outEnemies)
        outEnemies->clear();

    auto isValidEnemy = [&](BaseGameObject* obj)
    {
        return obj != nullptr &&
               obj->getOwnedByPlayerNumber() != baseGameObject.getOwnedByPlayerNumber() &&
               obj->getIsAlive() &&
               obj->getIsActive() &&
               obj->canDealDamage;
    };

    auto processPotentialEnemy = [&](BaseGameObject* obj)
    {
        if (!isValidEnemy(obj)) return;

        if (outEnemies)
            outEnemies->push_back(obj);

        float distance = distanceBetweenGameObjects(&baseGameObject, obj);
        if (distance < distanceClosestEnemy)
        {
            distanceClosestEnemy = distance;
            closestEnemy = obj;
        }
    };

    for (auto& object : gameObjects)
        processPotentialEnemy(object.get());

    for (auto& object : baseCharacters)
        processPotentialEnemy(object.get());

    processPotentialEnemy(player1);
    processPotentialEnemy(player2);

    if (closestEnemy != nullptr)
    {
        if (outDistance)
            *outDistance = distanceClosestEnemy;
    }

    return closestEnemy;
}





