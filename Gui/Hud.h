#ifndef GBFIGHTER_HUD_H
#define GBFIGHTER_HUD_H

#include "../Utils/AsepriteManager.h"
#include "Lifebar.h"

// Forward declaration of GameManager
class GameManager;

class Hud
{
public:
    Hud();
    ~Hud();

    void Draw();
    void Update(float deltaTime);
    void setLife1(int life);
    void setLife2(int life);
    void setSpecial1(int special);
    void setSpecial2(int special);

private:
    Lifebar* lifebar1;
    Lifebar* lifebar2;
    Lifebar* specialmeter1;
    Lifebar* specialmeter2;
    AsepriteAnimationFile* bgHUD;
    GameManager* gameManager;
};


#endif //GBFIGHTER_HUD_H
