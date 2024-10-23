#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "raylib.h"


enum MenuOptions
{
    PLAY,
    OPTIONS,
    EXIT,
    NUM_OPTIONS
};

class MenuState : public BaseState
{
public:
    MenuState(Game* game) : BaseState(game) {};
    void Enter() override;
    void Update() override;
    void Render() override;
    void Exit() override;

private:
    int selectedOption;
};

#endif
