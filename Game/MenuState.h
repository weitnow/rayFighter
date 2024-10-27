#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../Utils/AsepriteManager.h"
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
    MenuState(Game* game);
    ~MenuState();
    void Enter() override;
    void Update() override;
    void Render() override;
    void Exit() override;

private:
    int selectedOption;
    bool gameAboutToStart;
    AsepriteAnimationFile* aafTitleScreen;
    float timerInMs;
};

#endif
