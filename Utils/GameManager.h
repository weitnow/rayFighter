#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Characters/BaseCharacter.h"
#include "../GameObjects/BaseGameObject.h"
#include "Core.h"
#include <algorithm> // for std::remove and std::find

class GameManager
{
public:
    // Delete copy constructor and assignment operator to prevent copies of the singleton
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    // Method to access the single instance of the class
    static GameManager& getInstance();

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
    GameManager();

    // You can add a destructor and any private members or methods here if needed
    ~GameManager();

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

#endif //GAMEMANAGER_H
