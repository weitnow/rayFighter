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
    void Pause() override;
    void Resume() override;
    void Exit() override;

    void DrawSelectionScreen(int selectedIndex, int playerNumber);

private:
    AsepriteAnimationFile* CharSelectScreen;
    AsepriteAnimationFile* playerTag;

    List<Option> characters;

    int selectedCharacterP1 = 0;
    int selectedCharacterP2 = 3;

    bool selectingCharacter = true;

private:
    void PauseMusic();
    void ResumeMusic();
};

#endif
