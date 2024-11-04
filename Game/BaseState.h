#ifndef GB_BASE_STATE_H
#define GB_BASE_STATE_H

#include "Core.h"

//forward declarations
class Game;
class Screen2DManager;
class SoundManager;
class InputHandler;
class AsepriteManager;
class DebugInfo;
class CollisionManager;
class GameManager;
class BaseCharacter;
class BaseGameObject;
class BaseSpriteObject;


class BaseState
{
public:
    BaseState(Game* game);
    virtual ~BaseState();
    virtual void Enter();
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;

    // <-- GameState.h -->
    BaseCharacter* player1; // is a nullptr, set in GameState (and deleted when GameState is deleted)
    BaseCharacter* player2; // is a nullptr, set in GameState (and deleted when GameState is deleted)

protected:
    // <-- Game.h -->
    // Global components (pointers to single instances, loaded in Game.cpp)
    Game* game;
    Screen2DManager* screen2DManager;
    SoundManager* soundManager;
    InputHandler* inputHandler;
    AsepriteManager* asepriteManager;
    DebugInfo* debugInfo;
    GameManager* gameManager;
    CollisionManager* collisionManager; // is a nullptr, set in GameState (and deleted when GameState is deleted)
    float deltaTime;

    // <-- BaseState.h -->
    List<unique<BaseCharacter>> baseCharacters;
    List<unique<BaseGameObject>> gameObjects;
    List<unique<BaseSpriteObject>> baseSpriteObjects;

    // <-- GameState.h -->
    // Game Objects
    // float camPos;
    // AsepriteAnimationFile* background;
    // std::string randomBackground;

    // <-- MenuState.h -->
    // int selectedOption;
    // bool gameAboutToStart;
    // AsepriteAnimationFile* aafTitleScreen;
    // float timerInMs;
    // bool deadSoundPlayed;
};


#endif // GB_BASE_STATE_H
