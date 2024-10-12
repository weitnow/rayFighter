#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Characters/BaseCharacter.h"
#include "../GameObjects/BaseGameObject.h"
#include "Core.h"
#include <algorithm> // for std::remove and std::find

// Forward declaration of Lifebar
class Lifebar;

// Forward declaration of CollisionManager
class CollisionManager;

// Forward declaration of InputHandler
class InputHandler;

class GameManager
{
public:
    // Delete copy constructor and assignment operator to prevent copies of the singleton
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    // Method to access the single instance of the class
    static GameManager& getInstance();

    void init();

    // Public methods for managing game objects
    void addBaseCharacter(const std::string& CharName, BaseCharacter* character);
    void removeBaseCharacter(const std::string& CharName);
    BaseCharacter* getBaseCharacter(const std::string& CharName);

    void addBaseGameObject(BaseGameObject* object);
    void removeBaseGameObject();


    // Update and draw methods
    void update(float deltaTime);
    void draw();

    // InputHandler
    void addInputHandler(InputHandler* inputHandler);
    InputHandler* getInputHandler();

    // CollisionManager
    static CollisionManager& getCollisionManager();

    void addAsepriteManager(AsepriteManager* asepriteManager);
    AsepriteManager* getAsepriteManager();

    // deltaTimeMultiplier
    void setDeltaTimeMultiplier(float deltaTimeMultiplier);

    void playerKo(int playerNumber);


private:
    // Private constructor to prevent direct instantiation
    GameManager();

    // You can add a destructor and any private members or methods here if needed
    ~GameManager();

    // Private member variables to manage game objects
    Dictionary<std::string, BaseCharacter*> baseCharacters;
    List<BaseGameObject*> gameObjects;

    // AsepriteManager
    AsepriteManager* asepriteManager;

    // InputHandler
    InputHandler* inputHandler;

    // CollisionManager
    static CollisionManager collisionManager;

    bool player1and2set;
    // player 1 and player 2
    BaseCharacter* player1;
    BaseCharacter* player2;

    // Lifebars
    Lifebar* lifebar1;
    Lifebar* lifebar2;
    AsepriteAnimationFile* deadSkull;

    // deltaTimeMultiplier
    float deltaTimeMultiplier = 1.f;

    // member methodes
    void _setPlayer1and2();
    void _updateIsLeftPlayer1and2();
    void _checkCollisionsBetweenPlayers();
    void _checkHitsBetweenPlayers();
};

#endif //GAMEMANAGER_H
