#ifndef CHAR_SELECT_STATE_H
#define CHAR_SELECT_STATE_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/Core.h"
#include "BaseState.h"
#include "raylib.h"
#include <tuple>

struct Option
{
    Rectangle rect;
    std::string name;       // for example Andy
    std::string spritename; //for example gbFighter, nesFighter
    int spriteOffsetX = 0;
};

using PlayerStatus = std::tuple<bool, bool, bool, bool>; // onOrgPos, outsideScreen, movingIn, movingOut

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

    int selectedCharacterP1;
    int selectedCharacterP2;

    int activeCharacterP1; // which Character is currently seen on Screen
    int activeCharacterP2; // which Character is currently seen on Screen

    PlayerStatus p1status; // onOrgPos, outsideScreen, movingIn, movingOut
    PlayerStatus p2status; // onOrgPos, outsideScreen, movingIn, movingOut

    bool selectingCharacter = true;

    unique<BaseGameObject> p1;
    unique<BaseGameObject> p2;

    int p1posX = 45;  //x Position of P1
    int p2posX = 170; //x Position of P2


private:
    void PauseMusic();
    void ResumeMusic();
    void DrawSelectionScreen(int selectedIndex, int playerNumber);

    // Players
    void UpdatePlayers(float deltaTime);
    void DrawPlayers();
    void CharacterMoveControllerUpdate(int playerNumber);

    void _moveCharacterOffScreen(BaseGameObject& player);
    void _moveCharacterOnScreen(BaseGameObject& player);
    void _stopCharacterMovement(BaseGameObject& player);
    std::string getFrameTagStrOf(int playerNumber, std::string action);
};
#endif
