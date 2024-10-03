#include "State.h"
#include "../../Constants.h"
#include "../../Utils/GameManager.h"
#include "../../Utils/InputHandler.h"
#include "../../Utils/SoundManager.h"

GameManager& gameManager = GameManager::getInstance();
BaseCharacter* player1 = nullptr; // initialized by first time calling IdleState::Init()
BaseCharacter* player2 = nullptr; // initialized by first time calling IdleState::Init()
// each State class has a pointer to the owner BaseCharacter -> owner->getPos() or if(owner->isLeft()) etc.
// or if(ownwer->getPlayernumber() == 1) etc.
// each State class has a pointer to the controller -> controller->moveLeft = true; etc.
// each State class has a pointer to the statemachine -> statemachine->changeState("Walk"); etc.
InputHandler* inputHandler = nullptr; // initialized by first time calling IdleState::Init()

void State::setOwner(BaseCharacter* owner)
{
    this->owner = owner;
    controller = owner->getController();
    statemachine = &(owner->getStatemachine());
}

/* #region IdleState */
void IdleState::Init()
{
    /* #region Init local player1 and player2 ptr for easy access */
    // this code needs to run only once
    if (player1 == nullptr)
    {
        player1 = gameManager.getBaseCharacter("player1");
        if (player1 == nullptr) // if player1 is still nullptr
        {
            throw std::runtime_error("State.cpp -> Error: player1 not found in baseCharacters map.");
        }
    }
    if (player2 == nullptr)
    {
        player2 = gameManager.getBaseCharacter("player2");
    }
    if (inputHandler == nullptr)
    {
        inputHandler = gameManager.getInputHandler();
    }

    owner->stop(); // set moveVector.x = 0
    statemachine->changeState("Idle");
    std::cout << "IdleState Init" << std::endl;
}

void IdleState::Update(float deltaTime)
{
    // allowed transitions
    // walk, jump, duck, punch, kick, block, hit, hurt

    // Walk
    if (controller->moveLeft || controller->moveRight)
    {
        statemachine->changeState("Walk");
    }

    // Jump
    if (controller->jump)
    {
        statemachine->changeState("Jump");
    }

    // Duck
    if (controller->duck)
    {
        statemachine->changeState("Duck");
    }

    // Punch
    if (controller->punch)
    {
        statemachine->changeState("Punch");
    }
    else if (controller->kick)
    {
        statemachine->changeState("Kick");
    }
    else if (controller->block)
    {
        statemachine->changeState("Block");
    }
}

void IdleState::Finalize()
{
    std::cout << "IdleState Finalize" << std::endl;
}

/* #endregion */

/* #region WalkState */
void WalkState::Init()
{
    std::cout << "WalkState Init" << std::endl;

    statemachine->changeState("Walk");
}

void WalkState::Update(float deltaTime)
{

    if (!controller->moveLeft && !controller->moveRight)
    {
        statemachine->changeState("Idle");
    }

    // Walk
    if (controller->moveLeft)
    {
        owner->moveLeft();
    }
    else if (controller->moveRight)
    {
        owner->moveRight();
    }

    // Jump
    if (controller->jump)
    {
        statemachine->changeState("Jump");
    }
    // Duck
    else if (controller->duck)
    {
        statemachine->changeState("Duck");
    }

    // Punch
    if (controller->punch)
    {
        statemachine->changeState("Punch");
    }
    else if (controller->kick)
    {
        statemachine->changeState("Kick");
    }
    else if (controller->block)
    {
        statemachine->changeState("Block");
    }
}

void WalkState::Finalize()
{
    std::cout << "WalkState Finalize" << std::endl;
}
/* #endregion */

/* #region JumpState */
void JumpState::Init()
{
    std::cout << "JumpState Init" << std::endl;

    alreadyJumped = false;

    // check if player wants to move left or right while in the air, cannot change direction in the air
    if (controller->moveLeft)
    {
        goLeft = true;
    }
    else if (controller->moveRight)
    {
        goRight = true;
    }
}

void JumpState::Update(float deltaTime)
{
    // jump if not already jumped and is on the ground then jump
    if (owner->getIsOnGround() && alreadyJumped == false)
    {
        alreadyJumped = true;
        owner->jump();
    }
    // stop if already jumped and is on the ground and transition to idle
    else if (owner->getIsOnGround() && alreadyJumped == true)
    {
        statemachine->changeState("Idle");
    }

    // check if player wants to move left or right while in the air
    if (goLeft)
    {
        owner->moveLeft();
    }
    else if (goRight)
    {
        owner->moveRight();
    }
}

void JumpState::Finalize()
{
    std::cout << "JumpState Finalize" << std::endl;

    // reset the bools for next jump
    goLeft = false;
    goRight = false;
}
/* #endregion */

void DuckState::Init()
{
    // make sure the character cannot move while ducking
    owner->stop();
}

/* #region DuckState */
void DuckState::Update(float deltaTime)
{
    if (!controller->duck)
    {
        statemachine->changeState("Idle");
    }
}

void DuckState::Finalize()
{
}
/* #endregion */

/* #region PunchState */
void PunchState::Init()
{
    // make sure the character cannot move while punching
    owner->stop();

    // play punch sound //TODO: get rid of this
    SoundManager::getInstance().playSound(SoundManager::getInstance().punchSound);

    // add punch hitbox
    // if player1
    if (owner->getPlayerNumber() == 1)
    {
        // if player1 is left
        if (owner->getIsLeft())
        {
            // add punch hitbox to the left of player1
            owner->addCollisionBox("punch", 25, 10, 5, 5, CollisionBoxType::HITBOX, true, RED);
        }
        // if player1 is right
        else
        {
            // add punch hitbox to the right of player1
            owner->addCollisionBox("punch", 1, 10, 5, 5, CollisionBoxType::HITBOX, true, RED);
        }
    }
}

void PunchState::Update(float deltaTime)
{
    if (!controller->punch)
    {
        statemachine->changeState("Idle");
    }
}

void PunchState::Finalize()
{
    // remove punch hitbox
    owner->removeCollisionBox("punch");
}
/* #endregion */

/* #region KickState */
void KickState::Init()
{
}

void KickState::Update(float deltaTime)
{
}

void KickState::Finalize()
{
}
/* #endregion */

/* #region BlockState */
void BlockState::Init()
{
}

void BlockState::Update(float deltaTime)
{
}

void BlockState::Finalize()
{
}
/* #endregion */

/* #region HitState */
void HitState::Init()
{
}

void HitState::Update(float deltaTime)
{
}

void HitState::Finalize()
{
}
/* #endregion */

/* #region HurtState */
void HurtState::Init()
{
}

void HurtState::Update(float deltaTime)
{
}

void HurtState::Finalize()
{
}
/* #endregion */
