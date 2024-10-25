#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../Gui/Titlescreen.h"
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
    MenuState(Game* game) : BaseState(game), titleScreen(0, 0) {};
    void Enter() override;
    void Update() override;
    void Render() override;
    void Exit() override;

private:
    int selectedOption;
    Titlescreen titleScreen;
};

#endif
