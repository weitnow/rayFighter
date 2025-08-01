#include "Fighter2.h"
#include "../Utils/Input/InputHandler.h"
#include "Statemachine/Statemachine.h"


Fighter2::Fighter2(AsepriteManager* asepriteManager, float x, float y) : BaseCharacter(asepriteManager, x, y, "nesFighter-Idle")
{
}

Fighter2::~Fighter2()
{
}

void Fighter2::init()
{
    BaseCharacter::init();

    // Initialize the state machine with custom states
    auto customStateMap =
        getStatemachine().getDefaultStateMap(); // get default state map from statemachine with default behavior
    customStateMap["Kick"] = std::make_shared<PunchState>(); // override with custom state

    getStatemachine().init(customStateMap);

    setObjName("Ken Masters");

    // [0, 1, 2...] = frameNumber, -1 = valid for all frames of gbFigher (ex. gbFighter-*), -2 = valid for all frames of gbFighter-Action (ex. gbFighter-Idle)
    addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::PUSHBOX, 16, 0, 10, 30);

    addCollisionBoxForFrame("nesFighter-Punch", -2, CollisionBoxType::PROXIMITYBOX, 16, 0, 40, 32);
    addCollisionBoxForFrame("nesFighter-Punch", 0, CollisionBoxType::HITBOX, 30, 15, 5, 5);

    addCollisionBoxForFrame("nesFighter-DuckKick", -2, CollisionBoxType::PROXIMITYBOX, 16, 0, 40, 32);
    addCollisionBoxForFrame("nesFighter-DuckKick", 0, CollisionBoxType::HITBOX, 32, 17, 5, 5);

    addCollisionBoxForFrame("nesFighter-JumpPunch", -2, CollisionBoxType::PROXIMITYBOX, 16, 0, 40, 32);
    addCollisionBoxForFrame("nesFighter-JumpPunch", 0, CollisionBoxType::HITBOX, 28, 19, 5, 5);

    // x, y, width, height
    addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::HURTBOX, 10, 3, 12, 20, HurtboxType::HIGH);
    addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::HURTBOX, 10, 23, 12, 8, HurtboxType::LOW);

    addCollisionBoxForFrame("nesFighter-Idle",
                            -1,
                            CollisionBoxType::THROWABLEBOX,
                            16,
                            10,
                            12,
                            20,
                            HurtboxType::HIGH);

    getStatemachine().changeState("Idle");

    // draw shadow
    setDrawShadow(true);

    // set the life of the character
    setMaxLife(10);

    // set the power level of the character
    setMaxPowerLevel(2);
    setPowerLevel(1);

    setUpdateClosestEnemies(true); // updates <float>distanceToClosestEnemy, <BaseGameObject*>closestEnemyPtr, <std::vector<BaseGameObject*> allEnemies

    // set special moves
    specialMoves = {
        {"special1",
         {{InputDirection::Down, InputAction::None},
          {InputDirection::DownForward, InputAction::None},
          {InputDirection::Forward, InputAction::None},
          {InputDirection::Neutral, InputAction::Punch}}},
        {"special2",
         {{InputDirection::Backward, InputAction::None},
          {InputDirection::Down, InputAction::None},
          {InputDirection::Forward, InputAction::None},
          {InputDirection::Neutral, InputAction::Punch}}},
    };
}
