#ifndef OPTION_SELECT_STATE_H
#define OPTION_SELECT_STATE_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/Core.h"
#include "BaseState.h"
#include "raylib.h"


class OptionSelectState : public BaseState
{
public:
    OptionSelectState(Game* game);
    ~OptionSelectState();
    void Enter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Pause() override;
    void Resume() override;
    void Exit() override;
    void HandleInput() override;


private:
    AsepriteAnimationFile* OptionSelectScreen;

    int selectedOption; // tracks which resolution is currently highlighted
};

#endif
