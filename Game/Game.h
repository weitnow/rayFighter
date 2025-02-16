#ifndef GAME_H
#define GAME_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/Input/InputHandler.h"
#include "../Utils/Screen2DManager.h"
#include "../Utils/SoundManager.h"
#include "BaseState.h"
#include <memory>
#include <stack>


class Game
{

public:
    Game();
    ~Game();

    void ChangeState(std::unique_ptr<BaseState> newState);
    void PushState(std::unique_ptr<BaseState> newState);
    void PopState();
    void Update();
    void HandleInput(); // used for general input handling valid in every state
    void Render();
    bool quit;

public:
    // Global components
    Screen2DManager* screen2DManager;
    SoundManager* soundManager;
    InputHandler* inputHandler;
    AsepriteManager* asepriteManager;
    float deltaTime;

private:
    using StateStack = std::stack<std::unique_ptr<BaseState>>;

private:
    std::unique_ptr<BaseState> currentState;
    StateStack stateStack;
};

#endif
