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
    Fighter1* player1;
    Fighter2* player2;
    float deltaTime;
    float camPos;
};


#endif // GB_BASE_STATE_H
