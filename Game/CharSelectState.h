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
    void HandleInput() override;


private:
    AsepriteAnimationFile* CharSelectScreen;
    AsepriteAnimationFile* playerTag;

    List<Option> characters;

    int previousSelectedCharacterP1;
    int currentSelectedCharacterP1;
    int previousSelectedCharacterP2;
    int currentSelectedCharacterP2;

    bool selectingCharacter = true;

    unique<BaseGameObject> p1;
    unique<BaseGameObject> p2;


private:
    void PauseMusic();
    void ResumeMusic();
    void DrawSelectionScreen(int selectedIndex, int playerNumber);

    // Players
    void UpdatePlayers(float deltaTime);
    void DrawPlayers();
    void changePlayerCharacter(int playerNumber);
};

#endif
