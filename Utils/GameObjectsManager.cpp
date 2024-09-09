#include "GameObjectsManager.h"

// Define the static method to get the single instance of the class
GameObjectsManager& GameObjectsManager::getInstance()
{
    static GameObjectsManager instance; // This instance will be created the first time this method is called
    return instance;
}

// Private constructor definition
GameObjectsManager::GameObjectsManager() : player1(nullptr), player2(nullptr), player1and2set(false)
{
    // Initialize your game objects management here
}

// Optionally, define the destructor
GameObjectsManager::~GameObjectsManager()
{
    // Clean up resources if necessary
}

void GameObjectsManager::_updateIsLeftPlayer1and2()
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

void GameObjectsManager::_setPlayer1and2()
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

void GameObjectsManager::addBaseCharacter(const std::string& CharName, BaseCharacter* character)
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

void GameObjectsManager::removeBaseCharacter(const std::string& CharName)
{
    baseCharacters.erase(CharName);
}

// Define the methods to manage game objects
void GameObjectsManager::addObject()
{
    // Implementation of adding an object
}

void GameObjectsManager::removeObject()
{
    // Implementation of removing an object
}

void GameObjectsManager::update(float deltaTime)
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

    // Update other game objects
}

BaseCharacter* GameObjectsManager::getBaseCharacter(const std::string& CharName)
{
    if (baseCharacters.find(CharName) != baseCharacters.end())
    {
        return baseCharacters[CharName];
    }
    return nullptr;
}

void GameObjectsManager::draw()
{
    // Draw all baseCharacters
    for (auto& pair : baseCharacters)
    {
        pair.second->draw();
    }

    // Draw other game objects
}
