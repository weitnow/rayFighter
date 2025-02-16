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
    // [0, 1, 2...] = frameNumber, -1 = valid for all frames of the frameTagName, -2 = valid for all frames of the frameTagName
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 10, 0, 10, 30);
    addCollisionBoxForFrame("gbFighter-Punch", 1, CollisionBoxType::HITBOX, true, 26, 10, 5, 5);
    addCollisionBoxForFrame("gbFighter-Kick", 1, CollisionBoxType::HITBOX, true, 26, 10, 5, 5);
    addCollisionBoxForFrame("gbFighter-JumpPunch", 0, CollisionBoxType::HITBOX, true, 24, 20, 5, 5);
    addCollisionBoxForFrame("gbFighter-Idle", -2, CollisionBoxType::HURTBOX, HurtboxType::BODY, true, 10, 4, 12, 26);
    getStatemachine().changeState("Walk");


    // draw shadow
    setDrawShadow(true);
}
