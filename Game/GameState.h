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

    float middlePointXbetweenPlayers = 0.f;
    float middlePointYbetweenPlayers = 0.f;
    int BackgroundOffsetX = 0;
    int BackgroundOffsetY = 0;

    void _updateIsLeftPlayer1and2();
    void _checkCollisionsBetweenPlayers();
    void _checkHitsBetweenPlayers();
    void _updateCamera();     // scrools the background
    void _updateBackground(); // scrolls background in Y direction
};

#endif
