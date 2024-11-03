#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"
#include <raylib.h>

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
    // Game Objects
    float camPos;
};

#endif
