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

     Dictionary<std::string, std::shared_ptr<State>> customStateMap = {{"Idle", std::make_shared<IdleState>()},
                                                                      {"Walk", std::make_shared<WalkState>()},
                                                                      {"Jump", std::make_shared<JumpState>()},
                                                                      {"JumpPunch", std::make_shared<JumpPunchState>()},
                                                                      {"Duck", std::make_shared<DuckState>()},
                                                                      {"DuckPunch", std::make_shared<DuckKickState>()},
                                                                      {"DuckKick", std::make_shared<DuckKickState>()},
                                                                      {"DuckBlock", std::make_shared<DuckBlockState>()},
                                                                      {"Punch", std::make_shared<PunchState>()},
                                                                      {"Kick", std::make_shared<PunchState>()},
                                                                      {"Block", std::make_shared<BlockState>()},
                                                                      {"Hit", std::make_shared<HitState>()},
                                                                      {"Hurt", std::make_shared<HurtState>()},
                                                                      {"Death", std::make_shared<DeathState>()}};

    
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

    // set the life of the character
    setMaxLife(10);

    // set the power level of the character
    setMaxPowerLevel(2);
    setPowerLevel(1);
}
