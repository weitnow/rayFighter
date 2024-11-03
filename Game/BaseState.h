#ifndef BASE_STATE_H
#define BASE_STATE_H

//forward declarations
class Game;
class Screen2DManager;
class SoundManager;
class InputHandler;
class AsepriteManager;
class DebugInfo;
class GameManager;
class Fighter1;
class Fighter2;


class BaseState
{
public:
    BaseState(Game* game);
    virtual ~BaseState()
    {
    }
    virtual void Enter();
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;

protected:
    // Global components
    Game* game;
    Screen2DManager* screen2DManager;
    SoundManager* soundManager;
    InputHandler* inputHandler;
    AsepriteManager* asepriteManager;
    DebugInfo* debugInfo;
    GameManager* gameManager;
    Fighter1* player1; // is a nullptr, set in GameState (and deleted when GameState is deleted)
    Fighter2* player2; // is a nullptr, set in GameState (and deleted when GameState is deleted)
    float deltaTime;

    // <-- GameState.h -->
    // Game Objects
    // float camPos;
    // AsepriteAnimationFile* background;
    // std::string randomBackground;

    // <-- MenuState.h -->
    // int selectedOption;
    // bool gameAboutToStart;
    // AsepriteAnimationFile* aafTitleScreen;
    // float timerInMs;
    // bool deadSoundPlayed;
};


#endif // GB_BASE_STATE_H
