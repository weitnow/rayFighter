#ifndef CHAR_SELECT_STATE_H
#define CHAR_SELECT_STATE_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/Core.h"
#include "BaseState.h"
#include "raylib.h"

struct Option
{
    Rectangle rect;
    std::string name;
};

class CharSelectState : public BaseState
{
public:
    CharSelectState(Game* game);
    ~CharSelectState();
    void Enter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Exit() override;

    void DrawSelectionScreen(const List<Option>& options, int selectedIndex, const char* title);

private:
    AsepriteAnimationFile* CharSelectScreen;
    List<Option> characters;
    std::vector<Option> stages;

    int selectedCharacter = 0;
    int selectedStage = 0;
    bool selectingCharacter = true;
};

#endif
