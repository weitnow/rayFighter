#include "GameManager.h"

// Define the static method to get the single instance of the class
GameManager& GameManager::getInstance()
{
    static GameManager instance; // This instance will be created the first time this method is called
    return instance;
}

// Private constructor definition
GameManager::GameManager() : player1(nullptr), player2(nullptr), player1and2set(false)
{
    // Initialize your game objects management here
}

// Optionally, define the destructor
GameManager::~GameManager()
{
    // Clean up resources if necessary
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
    auto& player1CollisionBoxes = player1->getCollisionBoxes();
    auto& player2CollisionBoxes = player2->getCollisionBoxes();

    CollisionBox2D& player1CollisionBox = player1CollisionBoxes["Collisionbox"];
    CollisionBox2D& player2CollisionBox = player2CollisionBoxes["Collisionbox"];

    Rectangle& player1Rect = player1CollisionBox.getRectangle();
    Rectangle& player2Rect = player2CollisionBox.getRectangle();

    if (CheckCollisionRecs(player1Rect, player2Rect))
    {
        player1->setPos(player1->getPos().x - 1, player1->getPos().y);
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
void GameManager::addObject()
{
    // Implementation of adding an object
}

void GameManager::removeObject()
{
    // Implementation of removing an object
}

void GameManager::update(float deltaTime)
{
    // Set player1 and player2 if not already set
    _setPlayer1and2();

    // Update isLeft for player1 and player2
    _updateIsLeftPlayer1and2();


    // Update all baseCharacters
    for (auto& pair : baseCharacters)
    {
        pair.second->update(deltaTime);
    }

    _checkCollisionsBetweenPlayers();
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
    // Draw all baseCharacters
    for (auto& pair : baseCharacters)
    {
        pair.second->draw();
    }

    // Draw other game objects
}
