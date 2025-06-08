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

    void init(); // initialize the membervarialbes like player1, player2, selected Stage, etc.

    void ChangeState(std::unique_ptr<BaseState> newState);
    void PushState(std::unique_ptr<BaseState> newState);
    void PopState();
    void Update();
    void HandleInput(); // used for general input handling valid in every state
    void Render();
    bool quit;

public:
    // Global components
    SoundManager* soundManager; // SoundManager is a singleton, so we can use it directly
    std::unique_ptr<Screen2DManager> screen2DManager;
    std::unique_ptr<InputHandler> inputHandler;
    std::unique_ptr<AsepriteManager> asepriteManager;


    float deltaTime;
    int player1;
    int player2;
    int selectedStage;

private:
    using StateStack = std::stack<std::unique_ptr<BaseState>>;

private:
    std::unique_ptr<BaseState> currentState;
    StateStack stateStack;
};

#endif
