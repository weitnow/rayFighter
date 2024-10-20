#ifndef GAME_H
#define GAME_H

#include "../Characters/Fighter1.h"
#include "../Characters/Fighter2.h"
#include "../GameObjects/Items/Barrel.h"
#include "../Utils/AsepriteManager.h"
#include "../Utils/GameManager.h"
#include "../Utils/HelperFunctions.h"
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

    //private:
    std::unique_ptr<BaseState> currentState;

    // Global components
    Screen2DManager* screen2DManager;
    SoundManager* soundManager;
    InputHandler* inputHandler;
    AsepriteManager* asepriteManager;
    DebugInfo* debugInfo;
    GameManager* gameManager;
    AsepriteAnimationFile* background;
    Fighter1* player1;
    Fighter2* player2;
    std::unique_ptr<Barrel> barrel;
    float deltaTime;
    float camPos;
    std::string randomBackground;
};

#endif
