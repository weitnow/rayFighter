#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "raylib.h"

class MenuState : public BaseState
{
public:
    MenuState(Game* game) : BaseState(game) {};
    void Enter() override;
    void Update() override;
    void Render() override;
    void Exit() override;
};

#endif
