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
    void Exit() override;


private:
    AsepriteAnimationFile* OptionSelectScreen;


    int selectedStage = 0;


    bool selectingCharacter = true;
};

#endif
