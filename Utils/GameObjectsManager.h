#ifndef GAMEOBJECTSMANAGER_H
#define GAMEOBJECTSMANAGER_H

#include "../Characters/BaseCharacter.h"
#include "../GameObjects/BaseGameObject.h"
#include "Core.h"
#include <algorithm> // for std::remove and std::find

class GameObjectsManager
{
public:
    // Delete copy constructor and assignment operator to prevent copies of the singleton
    GameObjectsManager(const GameObjectsManager&) = delete;
    GameObjectsManager& operator=(const GameObjectsManager&) = delete;

    // Method to access the single instance of the class
    static GameObjectsManager& getInstance();

    // Public methods for managing game objects
    void addBaseCharacter(const std::string& CharName, BaseCharacter* character);
    void removeBaseCharacter(const std::string& CharName);
    void addObject();
    void removeObject();
    void update(float deltaTime);
    BaseCharacter* getBaseCharacter(const std::string& CharName);
    void draw();

private:
    // Private constructor to prevent direct instantiation
    GameObjectsManager();

    // You can add a destructor and any private members or methods here if needed
    ~GameObjectsManager();

    // Private member variables to manage game objects
    Dictionary<std::string, BaseCharacter*> baseCharacters;
    List<BaseGameObject*> gameObjects;

    bool player1and2set;
    // player 1 and player 2
    BaseCharacter* player1;
    BaseCharacter* player2;

    // member methodes
    void _setPlayer1and2();
    void _updateIsLeftPlayer1and2();
    void _checkCollisionsBetweenPlayers();
};

#endif //GAMEOBJECTSMANAGER_H
