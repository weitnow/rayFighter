#ifndef STAGE_SELECT_STATE_H
#define STAGE_SELECT_STATE_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/Core.h"
#include "BaseState.h"
#include "raylib.h"

struct StageOption
{
    Rectangle rect;
    std::string name;
};

class StageSelectState : public BaseState
{
public:
    StageSelectState(Game* game);
    ~StageSelectState();
    void Enter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Pause() override;
    void Resume() override;
    void Exit() override;

    void DrawSelectionScreen(int selectedIndex);

private:
    AsepriteAnimationFile* StageSelectScreen;

    List<StageOption> stages;


    int selectedStage = 0;


    bool selectingCharacter = true;
};

#endif
