#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "../Utils/AsepriteManager.h"
#include "BaseState.h"
#include "raylib.h"


class IntroState : public BaseState
{
public:
    IntroState(Game* game);
    ~IntroState();
    void Enter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Pause() override;
    void Resume() override;
    void Exit() override;
    void HandleInput() override;

private:
    int selectedOption;
    AsepriteAnimationFile* IntroScreen;
    float timerInMs;
};

#endif
