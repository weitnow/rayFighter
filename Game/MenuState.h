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
    explicit MenuState(Game* game);
    ~MenuState() override;
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
    bool optionAboutToStart;
    AsepriteAnimationFile* aafTitleScreen;
    bool deadSoundPlayed;
    Timer timer;

private:
    void PauseMusic();
    void ResumeMusic();
};

#endif
