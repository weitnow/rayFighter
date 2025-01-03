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
    void Update(float deltaTime) override;
    void Render() override;
    void Pause() override;
    void Resume() override;
    void Exit() override;
    void HandleInput() override;

private:
    int selectedOption;
    bool gameAboutToStart;
    AsepriteAnimationFile* aafTitleScreen;
    float timerInMs;
    bool deadSoundPlayed;

private:
    void PauseMusic();
    void ResumeMusic();
};

#endif
