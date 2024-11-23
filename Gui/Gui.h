#ifndef GBFIGHTER_GUI_H
#define GBFIGHTER_GUI_H

#include "../Utils/AsepriteManager.h"
#include "Lifebar.h"

class Game;

class Gui
{
public:
    Gui(Game* game);
    ~Gui();
    void draw();
    void update(float deltaTime);
    void setLife1(int life);
    void setLife2(int life);

private:
    Lifebar* lifebar1;
    Lifebar* lifebar2;

    AsepriteAnimationFile* bgUpperGui;
    AsepriteAnimationFile* bgLowerGui;
    Game* game;
};


#endif // GBFIGHTER_GUI_H
