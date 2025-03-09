#ifndef GBFIGHTER_GUI_H
#define GBFIGHTER_GUI_H

#include "../Game/BaseState.h"
#include "../Utils/AsepriteManager.h"
#include "Powerbar.h"

class Game;

class Gui
{
public:
    Gui(Game* game);
    ~Gui();
    void init(BaseState* state);
    void draw();
    void update(float deltaTime);
    void setLife1(int life);
    void setLife2(int life);
    void setPower1(int power);
    void setPower2(int power);
    void setWinningPoint1(int point);
    void setWinningPoint2(int point);

private:
    void _drawWinningPoints(int winningPoints, int playerNumber);
    void _drawPowSymbol();

private:
    Powerbar* lifebar1;
    Powerbar* lifebar2;
    Powerbar* powerbar1;
    Powerbar* powerbar2;
    int winningPoint1;
    int winningPoint2;
    int power1;
    int power2;

    AsepriteAnimationFile* bgUpperGui;
    AsepriteAnimationFile* bgLowerGui;
    AsepriteAnimationFile* winningPoint;
    Game* game;
    BaseState* state;
    bool initDone;


    int timer;
    double lastUpdateTime;
};


#endif // GBFIGHTER_GUI_H
