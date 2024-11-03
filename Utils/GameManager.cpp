#include "GameManager.h"
#include "../Constants.h"
#include "../Game/Game.h"
#include "../Gui/Hud.h"
#include "CollisionManager.h"
#include "SoundManager.h"

// Define the static member variable and pass the GameManager instance to the constructor
CollisionManager GameManager::collisionManager(GameManager::getInstance());

// Define the static method to get the single instance of the class
GameManager& GameManager::getInstance()
{
    static GameManager instance; // This instance will be created the first time this method is called
    return instance;
}

void GameManager::init()
{
    collisionManager.init();
}

// Private constructor definition
GameManager::GameManager()
    : player1(nullptr), player2(nullptr), player1and2set(false), game(nullptr), deltaTimeMultiplier(1.f)
{
    // Initialize the HUD
    hud = new Hud();
}

GameManager::~GameManager()
{
    // Clean up resources if necessary
    delete hud;
    hud = nullptr;
}

void GameManager::_updateIsLeftPlayer1and2()
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

void GameManager::_checkCollisionsBetweenPlayers()
{
    // Check if player1 and player2 are set
    if (!player1and2set)
    {
        return;
    }

    // Check if player1 and player2 are colliding
    // TODO: get rid of hardcoded [0]
    CollisionBox2D player1PushBox = player1->getPushBoxes()[0];
    CollisionBox2D player2PushBox = player2->getPushBoxes()[0];

    if (collisionManager.checkCollision(player1PushBox, player2PushBox))
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

void GameManager::_checkHitsBetweenPlayers()
{
    // TODO: refactor this, this stuff must be in the statemachine
    // loop through all hitboxes of player1
    for (auto& hitbox : player1->getHitBoxes())
    {
        // loop through all hurtboxes of player2
        for (auto& hurtbox : player2->getHurtBoxes())
        {
            if (collisionManager.checkCollision(hitbox, hurtbox) && player1->canDealDamage)
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

                SoundManager::getInstance().playSound("punchSound");
            }
        }
    }

    // loop through all hitboxes of player2
    for (auto& hitbox : player2->getHitBoxes())
    {
        // loop through all hurtboxes of player1
        for (auto& hurtbox : player1->getHurtBoxes())
        {
            if (collisionManager.checkCollision(hitbox, hurtbox) && player2->canDealDamage)
            {
                // Handle hit (you can define specific hit logic here)
                player1->takeDamage(1, &hitbox);
                player2->canDealDamage = false;

                SoundManager::getInstance().playSound("punchSound");
            }
        }
    }
}

void GameManager::_setPlayer1and2()
{
    // Check if player1 and player2 are set
    if (player1and2set)
        return;

    for (const auto& pair : baseCharacters)
    {
        BaseCharacter* character = pair.second;

        if (character->getPlayerNumber() == 1)
        {
            player1 = character;
        }
        else if (character->getPlayerNumber() == 2)
        {
            player2 = character;
        }

        // Exit loop early if both players are found
        if (player1 != nullptr && player2 != nullptr)
        {
            break;
        }
    }

    if (!player1)
    {
        throw std::runtime_error("Error: player1 not found in baseCharacters map.");
    }

    if (!player2)
    {
        throw std::runtime_error("Error: player2 not found in baseCharacters map.");
    }

    player1and2set = true;
}

void GameManager::addBaseCharacter(const std::string& CharName, BaseCharacter* character)
{
    // check if the character already exists and if so, raise an error
    if (baseCharacters.find(CharName) != baseCharacters.end())
    {
        throw std::runtime_error("baseCharacter with CharName " + CharName +
                                 " already exists"
                                 "\n Cannot add it again. GameObjectsManager::addBaseCharacter");
        return;
    }


    baseCharacters[CharName] = character;
}

void GameManager::removeBaseCharacter(const std::string& CharName)
{
    baseCharacters.erase(CharName);
}

// Define the methods to manage game objects
void GameManager::addBaseGameObject(BaseGameObject* object)
{
    gameObjects.push_back(object);
}

void GameManager::removeBaseGameObject()
{
    // Implementation of removing an object
    throw std::runtime_error("GameManager::removeBaseGameObject -> Not implemented yet.");
}

void GameManager::addBaseSpriteObject(BaseSpriteObject* object)
{
    baseSpriteObjects.push_back(object);
}

void GameManager::removeBaseSpriteObject()
{
    // Implementation of removing an object
    throw std::runtime_error("GameManager::removeBaseSpriteObject -> Not implemented yet.");
}

void GameManager::update(float deltaTime)
{
    // Multiply deltaTime by deltaTimeMultiplier (can be used to speed up or slow down the game)
    deltaTime *= deltaTimeMultiplier;

    // Set player1 and player2 if not already set
    _setPlayer1and2();

    // Update isLeft for player1 and player2
    _updateIsLeftPlayer1and2();

    _checkHitsBetweenPlayers();

    // Update all gameObjects
    for (auto& object : gameObjects)
    {
        object->update(deltaTime);
    }

    // Update all baseCharacters
    for (auto& pair : baseCharacters)
    {
        pair.second->update(deltaTime);
    }

    // Update the collision manager
    collisionManager.update(deltaTime);

    _checkCollisionsBetweenPlayers();


    // Update the HUD
    hud->Update(deltaTime);

    // calculate middlePointXbetweenPlayers
    middlePointXbetweenPlayers = (player1->getPos().x + player2->getPos().x + 32) / 2.f;
}

BaseCharacter* GameManager::getBaseCharacter(const std::string& CharName)
{
    if (baseCharacters.find(CharName) != baseCharacters.end())
    {
        return baseCharacters[CharName];
    }
    std::cerr << "GameManager::getBaseCharacter -> BaseCharacter with name " << CharName
              << " not found in baseCharacters map." << std::endl;
    return nullptr;
}

void GameManager::draw()
{
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
    for (auto& pair : baseCharacters)
    {
        pair.second->draw();
    }

    // Draw a white rectangle for UpperGui
    DrawRectangle(0, 0, 256, 40, WHITE);

    // Draw the HUD
    hud->Draw();

    if (Global::debugMode)
    {
        // Draw the middlePointXbetweenPlayers
        DrawLine(middlePointXbetweenPlayers, 0, middlePointXbetweenPlayers, 300, RED);
    }
}

void GameManager::addInputHandler(InputHandler* inputHandler)
{
    this->inputHandler = inputHandler;
}

InputHandler* GameManager::getInputHandler()
{
    if (inputHandler == nullptr)
    {
        std::cerr << "GameManager::getInputHandler -> InputHandler not set." << std::endl;
    }
    return inputHandler;
}

CollisionManager& GameManager::getCollisionManager()
{
    return collisionManager;
}

void GameManager::addGameInstance(Game* game)
{
    this->game = game;
}

void GameManager::addAsepriteManager(AsepriteManager* asepriteManager)
{
    if (asepriteManager == nullptr)
    {
        throw std::runtime_error("AsepriteManager is nullptr");
    }

    this->asepriteManager = asepriteManager;
}

AsepriteManager* GameManager::getAsepriteManager()
{
    if (asepriteManager == nullptr)
    {
        throw std::runtime_error("GameManager::getAsepriteManager -> asepriteManager is nullptr.");
    }
    this->asepriteManager;
}

void GameManager::setDeltaTimeMultiplier(float deltaTimeMultiplier)
{
    this->deltaTimeMultiplier = deltaTimeMultiplier;
}

void GameManager::playerKo(int playerNumber)
{
    //bgHUD->setFrameTag("bgUpperGui-Amazed");
}

void GameManager::setDebugMode(bool debugMode)
{
    Global::debugMode = debugMode;
    Global::debugWindow = debugMode;
    Global::debugSpriteBorder = false; //debugMode;
    Global::debugCollisionBoxes = debugMode;
    Global::debugHitboxes = debugMode;
    Global::debugHurtboxes = debugMode;
    Global::debugPushboxes = false;  //debugMode;
    Global::debugThrowboxes = false; //debugMode;

    if (debugMode)
    {
        if (game == nullptr)
        {
            throw std::runtime_error("GameManager::setDebugMode -> Game instance not set.");
        }
        std::cout << "DebugMode is set to true" << std::endl;

        // Add gameObjects to the debugInfo
        game->debugInfo->addGameObject("Player1", game->player1);
        game->debugInfo->addGameObject("Player2", game->player2);
        game->debugInfo->addGameObject(
            "Barrel",
            game->barrel.get()); // dangerous, because the unique pointer is not copied //TODO: get rid of this

        // change resolution of the renderTarget
        game->screen2DManager->setResolution(Resolution::R_1120x630);
    }
    else
    {
        std::cout << "DebugMode is set to false" << std::endl;
        // change resolution of the renderTarget
        game->screen2DManager->setResolution(Resolution::R_1920x1080);
    }
}

BaseCharacter* GameManager::getPlayer1()
{
    if (player1 == nullptr)
    {
        throw std::runtime_error("GameManager::getPlayer1 -> player1 is nullptr.");
    }

    return player1;
}

BaseCharacter* GameManager::getPlayer2()
{
    if (player2 == nullptr)
    {
        throw std::runtime_error("GameManager::getPlayer2 -> player2 is nullptr.");
    }
    return player2;
}
