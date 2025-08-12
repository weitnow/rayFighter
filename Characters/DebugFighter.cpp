#include "DebugFighter.h"
#include "../Utils/Input/InputHandler.h"
#include "Statemachine/Statemachine.h"


DebugFighter::DebugFighter(AsepriteManager* asepriteManager, float x, float y) : BaseCharacter(asepriteManager, x, y, "debugFighter-Idle")
{
}

DebugFighter::~DebugFighter()
{
}

void DebugFighter::init()
{
    BaseCharacter::init();

    // Initialize the state machine with custom states
    auto customStateMap =
        getStatemachine().getDefaultStateMap(); // get default state map from statemachine with default behavior
    customStateMap["Special1"] = std::make_shared<F1Special1State>(); // override with custom state
    customStateMap["Special2"] = std::make_shared<F1Special2State>(); // override with custom state
    customStateMap["Special3"] = std::make_shared<F1Special3State>(); // override with custom state

    getStatemachine().init(customStateMap);

    setObjName("Andy Hug");

    // [0, 1, 2...] = frameNumber, -1 = valid for all frames of gbFigher (ex. debugFighter-*), -2 = valid for all frames of debugFighter-Action (ex. debugFighter-Idle)
    addCollisionBoxForFrame("debugFighter-Idle", -1, CollisionBoxType::PUSHBOX, 10, 0, 10, 30);

    addCollisionBoxForFrame("debugFighter-Punch", -2, CollisionBoxType::PROXIMITYBOX, 16, 0, 40, 32);
    addCollisionBoxForFrame("debugFighter-Punch", 1, CollisionBoxType::HITBOX, 31, 10, 5, 5);

    addCollisionBoxForFrame("debugFighter-Kick", -2, CollisionBoxType::PROXIMITYBOX, 16, 0, 40, 32);
    addCollisionBoxForFrame("debugFighter-Kick", 1, CollisionBoxType::HITBOX, 26, 10, 5, 5);

    addCollisionBoxForFrame("debugFighter-DuckKick", -2, CollisionBoxType::PROXIMITYBOX, 16, 0, 40, 32);
    addCollisionBoxForFrame("debugFighter-DuckKick", 1, CollisionBoxType::HITBOX, 26, 26, 5, 5);

    addCollisionBoxForFrame("debugFighter-DuckPunch", -2, CollisionBoxType::PROXIMITYBOX, 16, 0, 40, 32);
    addCollisionBoxForFrame("debugFighter-DuckPunch", 0, CollisionBoxType::HITBOX, 30, 14, 5, 5);

    addCollisionBoxForFrame("debugFighter-JumpPunch", -2, CollisionBoxType::PROXIMITYBOX, 16, 0, 40, 32);
    addCollisionBoxForFrame("debugFighter-JumpPunch", 0, CollisionBoxType::HITBOX, 24, 20, 5, 5);

    // special moves
    addCollisionBoxForFrame("debugFighter-A+B Move", -2, CollisionBoxType::PROXIMITYBOX, 16, 0, 40, 32);
    addCollisionBoxForFrame("debugFighter-A+B Move", -2, CollisionBoxType::HITBOX, 0, 0, 35, 30);

    // x, y, width, height
    addCollisionBoxForFrame("debugFighter-Idle", -1, CollisionBoxType::HURTBOX, 10, 3, 12, 20, HurtboxType::HIGH);
    addCollisionBoxForFrame("debugFighter-Idle", -1, CollisionBoxType::HURTBOX, 10, 23, 12, 8, HurtboxType::LOW);

    //addCollisionBoxForFrame("debugFighter-Idle", -1, CollisionBoxType::THROWBOX, HurtboxType::HIGH, true, 16, 10, 12, 20);

    addCollisionBoxForFrame("debugFighter-Idle",
                            -1,
                            CollisionBoxType::THROWABLEBOX,
                            16,
                            10,
                            12,
                            20,
                            HurtboxType::HIGH);


    getStatemachine().changeState("Walk");

    // draw shadow
    setDrawShadow(true);

    // set the life of the character
    setMaxLife(6);

    // set the power level of the character
    setMaxPowerLevel(3);
    setPowerLevel(3);

    setUpdateClosestEnemies(
        true); // updates <float>distanceToClosestEnemy, <BaseGameObject*>closestEnemyPtr, <std::vector<BaseGameObject*> allEnemies

    // set special moves
    specialMoves = {{"special1", // Fireball
                     {{InputDirection::Down, InputAction::None},
                      {InputDirection::DownForward, InputAction::None},
                      {InputDirection::Forward, InputAction::None},
                      {InputDirection::Forward, InputAction::Punch}}},
                    {"special2", // Hurricane Kick
                     {{InputDirection::Down, InputAction::None},
                      {InputDirection::Down, InputAction::None},
                      {InputDirection::Up, InputAction::None}}},
                    {"special3", // Spear
                     {
                         {InputDirection::Backward, InputAction::None},
                         {InputDirection::Backward, InputAction::None},
                         {InputDirection::Forward, InputAction::None},
                         {InputDirection::Neutral, InputAction::Punch},

                     }}

    };
}
