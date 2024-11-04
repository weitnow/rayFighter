#ifndef GAMESTATE_H
#define GAMESTATE_H

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
    virtual void Update() override;
    virtual void Render() override;
    virtual void Exit() override;

protected:
    float camPos;
    AsepriteAnimationFile* background;
    std::string randomBackground;

    float middlePointXbetweenPlayers = 0.f;

    void setDebugMode(bool debugMode);
    void _updateIsLeftPlayer1and2();
    void _checkCollisionsBetweenPlayers();
    void _checkHitsBetweenPlayers();
};

#endif
