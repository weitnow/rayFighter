#include "Fighter1.h"
#include "../Utils/Input/InputHandler.h"
#include "Statemachine/Statemachine.h"


Fighter1::Fighter1(AsepriteManager* asepriteManager, float x, float y) : BaseCharacter(asepriteManager, x, y)
{
}

Fighter1::~Fighter1()
{
}

void Fighter1::init()
{
    BaseCharacter::init();
    setCurrentFrameTag("gbFighter-Idle"); // using gbFighter-Graphics
    setObjName("Andy");
    setPlayerNumber(1);
    // [0, 1, 2...] = frameNumber, -1 = valid for all frames of gbFigher (ex. gbFighter-*), -2 = valid for all frames of gbFighter-Action (ex. gbFighter-Idle)
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 10, 0, 10, 30);

    addCollisionBoxForFrame("gbFighter-Punch", 1, CollisionBoxType::HITBOX, true, 31, 10, 5, 5);
    addCollisionBoxForFrame("gbFighter-Kick", 1, CollisionBoxType::HITBOX, true, 26, 10, 5, 5);
    addCollisionBoxForFrame("gbFighter-DuckKick", 1, CollisionBoxType::HITBOX, true, 26, 26, 5, 5);
    addCollisionBoxForFrame("gbFighter-DuckPunch", 0, CollisionBoxType::HITBOX, true, 30, 14, 5, 5);
    addCollisionBoxForFrame("gbFighter-JumpPunch", 0, CollisionBoxType::HITBOX, true, 24, 20, 5, 5);

    // x, y, width, height
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::HEAD, true, 10, 3, 12, 10);
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::BODY, true, 10, 13, 12, 10);
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::LEGS, true, 10, 23, 12, 8);


    getStatemachine().changeState("Walk");

    // draw shadow
    setDrawShadow(true);

    // set the life of the character
    setMaxLife(6);

    // set the power level of the character
    setPowerLevel(2);
}
