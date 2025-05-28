#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../Gui/Gui.h"
#include "BaseState.h"
#include <raylib.h>
#include <string>

// forward declarations
class AsepriteAnimationFile;
class GameState : public BaseState
{
public: // METHODES
    GameState(Game* game);
    virtual ~GameState();
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    void Pause() override;
    void Resume() override;
    virtual void Exit() override;
    void HandleInput() override;

    BaseCharacter* createPlayer(int characterNumber, int playerNumber);


    Vector2 getMiddlePointBetweenPlayers() const;
    int _getScreenPosXofObject(BaseGameObject& object);

public: // VARIABLES
    // <-- BaseState.h -->
    // Screen2DManager* screen2DManager;
    // BaseCharacter* player1;
    // BaseCharacter* player2;

    // <-- GameState.h -->
    int cameraX = 0; // will be updated in GameState::_updateCamera
    int cameraY = 0;

protected: // METHODES
    void _updateMiddlePointBetweenPlayers();
    void _updateIsLeftPlayer1and2();
    void _checkPushCollisionsBetweenPlayers();
    void _keepPlayersOnStage();
    void _updateCamera(bool restriction = true); // if restriction is true, the camera is restricted to the stage
    void _updateAllGameObjects(float deltaTime);
    void _updateAllBaseCharacters(float deltaTime);

protected: // VARIABLES
    /* <-- Game.h -->
    Game* game;
    SoundManager* soundManager;
    InputHandler* inputHandler;
    AsepriteManager* asepriteManager;
    DebugInfo* debugInfo;
    float deltaTime;

    // <-- BaseState.h -->
    CharacterController* player1Controller;
    CharacterController* player2Controller;
    */

    // <-- GameState.h -->
    List<unique<BaseCharacter>> baseCharacters;
    List<unique<BaseGameObject>> gameObjects;
    AsepriteAnimationFile* levelAnimFile;
    Gui* gui;

    int middlePointXbetweenPlayers = 0; // will be updated in _updateMiddlePointBetweenPlayers
    int middlePointYbetweenPlayers = 0;
};

#endif
