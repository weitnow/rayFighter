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
public:
    GameState(Game* game);
    virtual ~GameState();
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Exit() override;

    Vector2 getMiddlePointBetweenPlayers() const;
    int _getScreenPosXofObject(BaseGameObject& object);


    int cameraX = 0; // will be updated in _updateCamera
    int cameraY = 0;

protected:
    AsepriteAnimationFile* levelAnimFile;
    Gui* gui;

    int middlePointXbetweenPlayers = 0; // will be updated in _updateMiddlePointBetweenPlayers
    int middlePointYbetweenPlayers = 0;

    void _updateMiddlePointBetweenPlayers();
    void _updateIsLeftPlayer1and2();
    void _checkCollisionsBetweenPlayers();
    void _checkHitsBetweenPlayers();
    void _keepPlayersOnStage();
    void _updateCamera(bool restriction = true); // if restriction is true, the camera is restricted to the stage
};

#endif
