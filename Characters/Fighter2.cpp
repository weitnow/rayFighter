#include "Fighter2.h"
#include "../Utils/GameManager.h"
#include "../Utils/InputHandler.h"
#include "Statemachine/Statemachine.h"


Fighter2::Fighter2(AsepriteManager* asepriteManager, float x, float y) : BaseCharacter(asepriteManager, x, y)
{
}

Fighter2::~Fighter2()
{
}

void Fighter2::init()
{
    setLife(2);                            // Todo: get rid of setLife
    setCurrentFrameTag("nesFighter-Idle"); // using nesFighter-Graphics
    setObjName("Ken");
    setPlayerNumber(2);
    addController(GameManager::getInstance().getInputHandler()->getPlayer2Controller());
    addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 16, 0, 10, 30);
    addCollisionBoxForFrame("nesFighter-Punch", 0, CollisionBoxType::HITBOX, true, 30, 15, 5, 5);
    addCollisionBoxForFrame("nesFighter-Idle", -2, CollisionBoxType::HURTBOX, HurtboxType::BODY, true, 10, 4, 12, 26);
    getStatemachine().changeState("Idle");
    setSpriteOffsetX(5);
}