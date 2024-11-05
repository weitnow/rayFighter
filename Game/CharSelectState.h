#ifndef CHAR_SELECT_STATE_H
#define CHAR_SELECT_STATE_H

#include "../Utils/AsepriteManager.h"
#include "BaseState.h"
#include "raylib.h"


class CharSelectState : public BaseState
{
public:
    CharSelectState(Game* game);
    ~CharSelectState();
    void Enter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Exit() override;

private:
};

#endif
