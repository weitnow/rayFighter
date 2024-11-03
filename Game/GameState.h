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
    // Game Objects
    float camPos;
    AsepriteAnimationFile* background;
    std::string randomBackground;
};

#endif
