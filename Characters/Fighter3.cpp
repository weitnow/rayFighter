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

    // Initialize the state machine with custom states
    auto customStateMap = getStatemachine().getDefaultStateMap(); // get default state map from statemachine with default behavior
    //customStateMap["Idle"] = std::make_shared<F1IdleState>(); // override with custom state

    getStatemachine().init(customStateMap); 

    setCurrentFrameTag("gbFighter-Idle"); // using nesFighter-Graphics
    setObjName("Shang Tsung");


    // [0, 1, 2...] = frameNumber, -1 = valid for all frames of gbFigher (ex. gbFighter-*), -2 = valid for all frames of gbFighter-Action (ex. gbFighter-Idle)
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 10, 0, 10, 30);
    addCollisionBoxForFrame("gbFighter-Punch", 1, CollisionBoxType::HITBOX, true, 31, 10, 5, 5);
    addCollisionBoxForFrame("gbFighter-Kick", 1, CollisionBoxType::HITBOX, true, 26, 10, 5, 5);
    addCollisionBoxForFrame("gbFighter-DuckKick", 1, CollisionBoxType::HITBOX, true, 26, 26, 5, 5);
    addCollisionBoxForFrame("gbFighter-DuckPunch", 0, CollisionBoxType::HITBOX, true, 30, 14, 5, 5);
    addCollisionBoxForFrame("gbFighter-JumpPunch", 0, CollisionBoxType::HITBOX, true, 24, 20, 5, 5);
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::HEAD, true, 10, 3, 12, 10);
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::BODY, true, 10, 13, 12, 10);
    addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::LEGS, true, 10, 23, 12, 8);

    // [0, 1, 2...] = frameNumber, -1 = valid for all frames of gbFigher (ex. gbFighter-*), -2 = valid for all frames of gbFighter-Action (ex. gbFighter-Idle)
    addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 16, 0, 10, 30);
    addCollisionBoxForFrame("nesFighter-Punch", 0, CollisionBoxType::HITBOX, true, 30, 15, 5, 5);
    addCollisionBoxForFrame("nesFighter-DuckKick", 0, CollisionBoxType::HITBOX, true, 32, 17, 5, 5);
    addCollisionBoxForFrame("nesFighter-JumpPunch", 0, CollisionBoxType::HITBOX, true, 28, 19, 5, 5);
    addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::HEAD, true, 10, 3, 12, 10);
    addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::BODY, true, 10, 13, 12, 10);
    addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::LEGS, true, 10, 23, 12, 8);


    getStatemachine().changeState("Idle");

    // draw shadow
    setDrawShadow(true);

    // set the life of the character
    setMaxLife(10);

    // set the power level of the character
    setMaxPowerLevel(2);
    setPowerLevel(1);

    // set special moves
    specialMoves = {
        {"Fireball",
         {{InputDirection::Down, InputAction::None},
          {InputDirection::DownForward, InputAction::None},
          {InputDirection::Forward, InputAction::None},
          {InputDirection::Neutral, InputAction::Punch}}},
        {"Spear",
         {{InputDirection::Backward, InputAction::None},
          {InputDirection::Down, InputAction::None},
          {InputDirection::Forward, InputAction::None},
          {InputDirection::Neutral, InputAction::Punch}}},
    };
}
