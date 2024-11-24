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


protected:
    AsepriteAnimationFile* background;
    std::string randomBackground;
    Gui* gui;

    int middlePointXbetweenPlayers = 0;
    int middlePointYbetweenPlayers = 0;

    int cameraX = 0;
    int cameraY = 0;

    int playerXGlobal = 0;
    int playerYGlobal = 0;

    void _updateMiddlePointBetweenPlayers();
    void _updateIsLeftPlayer1and2();
    void _checkCollisionsBetweenPlayers();
    void _checkHitsBetweenPlayers();
    void _keepPlayersOnStage();
    void _updateCamera(bool restriction = true); // if restriction is true, the camera is restricted to the stage
};

#endif
