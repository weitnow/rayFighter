#ifndef GB_BASE_STATE_H
#define GB_BASE_STATE_H

#include "../Utils/HelperFunctions.h"
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
class CharacterController;


class BaseState
{
public: // member methods
    BaseState(Game* game);
    virtual ~BaseState();
    virtual void Enter();
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Exit() = 0;
    virtual void HandleInput() = 0;

public: // member variables
    // <-- Game.h -->
    // Global components (pointers to single instances, loaded in Game.cpp)

    // <-- BaseState.h -->
    Screen2DManager* screen2DManager;
    BaseCharacter* player1; // is a nullptr, set in GameState (and deleted when GameState is deleted)
    BaseCharacter* player2; // is a nullptr, set in GameState (and deleted when GameState is deleted)

protected: // member variables
    // <-- Game.h -->
    // Global components (pointers to single instances, loaded in Game.cpp)
    Game* game;
    SoundManager* soundManager;
    InputHandler* inputHandler;
    AsepriteManager* asepriteManager;
    DebugInfo* debugInfo;
    float deltaTime;

    // <-- BaseState.h -->
    CharacterController* player1Controller;
    CharacterController* player2Controller;

    // <-- GameState.h -->
    // List<unique<BaseCharacter>> baseCharacters;
    // List<unique<BaseGameObject>> gameObjects;
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
