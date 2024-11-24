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

protected:
    float camPos;
    AsepriteAnimationFile* background;
    std::string randomBackground;
    Gui* gui;

    int middlePointXbetweenPlayers = 0;
    int middlePointYbetweenPlayers = 0;
    int BackgroundOffsetX = 0;
    int BackgroundOffsetY = 0;

    void _updateMiddlePointBetweenPlayers();
    void _updateIsLeftPlayer1and2();
    void _checkCollisionsBetweenPlayers();
    void _checkHitsBetweenPlayers();
    void _updateCamera();
};

#endif
