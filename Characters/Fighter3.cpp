#include "Fighter3.h"
#include "../Utils/Input/InputHandler.h"
#include "Statemachine/Statemachine.h"


Fighter3::Fighter3(AsepriteManager* asepriteManager, float x, float y) : BaseCharacter(asepriteManager, x, y)
{
}

Fighter3::~Fighter3()
{
}

void Fighter3::init()
{
    BaseCharacter::init();
    setCurrentFrameTag("gbFighter-Idle"); // using nesFighter-Graphics
    setObjName("Shang T.");
    setPlayerNumber(1);

    // [0, 1, 2...] = frameNumber, -1 = valid for all frames of gbFigher (ex. nesFighter-*), -2 = valid for all frames of nesFighter-Action (ex. nesFighter-Idle)
    addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 16, 0, 10, 30);
    addCollisionBoxForFrame("nesFighter-Punch", 0, CollisionBoxType::HITBOX, true, 30, 15, 5, 5);
    addCollisionBoxForFrame("nesFighter-Idle", -2, CollisionBoxType::HURTBOX, HurtboxType::BODY, true, 10, 4, 12, 26);

    // [0, 1, 2...] = frameNumber, -1 = valid for all frames of gbFigher (ex. gbFighter-*), -2 = valid for all frames of gbFighter-Action (ex. gbFighter-Idle)
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 10, 0, 10, 30);
    addCollisionBoxForFrame("gbFighter-Punch", 1, CollisionBoxType::HITBOX, true, 31, 10, 5, 5);
    addCollisionBoxForFrame("gbFighter-Kick", 1, CollisionBoxType::HITBOX, true, 26, 10, 5, 5);
    addCollisionBoxForFrame("gbFighter-JumpPunch", 0, CollisionBoxType::HITBOX, true, 24, 20, 5, 5);
    addCollisionBoxForFrame("gbFighter-Idle", -2, CollisionBoxType::HURTBOX, HurtboxType::BODY, true, 10, 4, 12, 26);


    getStatemachine().changeState("Idle");

    // draw shadow
    setDrawShadow(true);
}
