#ifndef GAME_H
#define GAME_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/InputHandler.h"
#include "../Utils/Screen2DManager.h"
#include "../Utils/SoundManager.h"
#include "BaseState.h"
#include <memory>


class Game
{

public:
    Game();
    ~Game();

    void ChangeState(std::unique_ptr<BaseState> newState);
    void Update();
    void Render();
    bool quit;

    //private:
    std::unique_ptr<BaseState> currentState;

    // Global components
    Screen2DManager* screen2DManager;
    SoundManager* soundManager;
    InputHandler* inputHandler;
    AsepriteManager* asepriteManager;
    GameManager* gameManager;

    float deltaTime;
};

#endif
