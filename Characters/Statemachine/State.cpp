#include "State.h"
#include "../../Constants.h"
#include "../../Utils/InputHandler.h"
#include "../../Utils/SoundManager.h"

// each State class has a pointer to the owner BaseCharacter -> owner->getPos() or if(owner->isLeft()) etc.
// or if(ownwer->getPlayernumber() == 1) etc.
// each State class has a pointer to the controller -> controller->moveLeft = true; etc.
// each State class has a pointer to the statemachine -> statemachine->changeState("Walk"); etc.
InputHandler* inputHandler = nullptr; // initialized by first time calling IdleState::Init()

void State::setOwner(BaseCharacter* owner)
{
    this->owner = owner;
    statemachine = &(owner->getStatemachine());
    controller = owner->getController();
}

/* #region IdleState */
void IdleState::Init()
{
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

    // check if last state was jumpPunch
    if (owner->getStatemachine().getPreviousStateAsString() == "JumpPunch")
    {
        std::cout << "JumpState Init -> last state was JumpPunch" << std::endl;
        alreadyJumped = true;
    }

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

    // check if player moved left or right at the start of the jump
    if (goLeft)
    {
        owner->moveLeft();
    }
    else if (goRight)
    {
        owner->moveRight();
    }

    // check if player is punching or kicking
    if (controller->punch)
    {
        statemachine->changeState("JumpPunch");
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

void JumpPunchState::Init()
{
    owner->canDealDamage = true;

    // play sound
    SoundManager::getInstance().playSound("mk2/punchSound.mp3");
}

void JumpPunchState::Update(float deltaTime)
{
    if (owner->getAnim()->hasAnimJustFinishedPlusLastFrameDuration())
    {
        statemachine->changeState("Jump");
    }
}

void JumpPunchState::Finalize()
{
}

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

    // check if player is punching or kicking or blocking
    if (controller->punch)
    {
        statemachine->changeState("DuckPunch");
    }
    else if (controller->kick)
    {
        statemachine->changeState("DuckKick");
    }
    else if (controller->block)
    {
        statemachine->changeState("DuckBlock");
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
    owner->canDealDamage = true;

    // play sound
    SoundManager::getInstance().playSound("mk2/punchSound.mp3");
}

void PunchState::Update(float deltaTime)
{
    if (owner->getAnim()->hasAnimJustFinishedPlusLastFrameDuration())
    {
        statemachine->changeState("Idle");
    }
}

void PunchState::Finalize()
{
}
/* #endregion */

void DuckPunchState::Init()
{
    owner->canDealDamage = true;

    // play sound
    SoundManager::getInstance().playSound("mk2/punchSound.mp3");
}

void DuckPunchState::Update(float deltaTime)
{
    if (owner->getAnim()->hasAnimJustFinishedPlusLastFrameDuration())
    {
        statemachine->changeState("Duck");
    }
}

void DuckPunchState::Finalize()
{
}

/* #region KickState */
void KickState::Init()
{
    // make sure the character cannot move while punching
    owner->stop();
    owner->canDealDamage = true;

    // play sound
    SoundManager::getInstance().playSound("mk2/punchSound.mp3");
}

void KickState::Update(float deltaTime)
{
    if (owner->getAnim()->hasAnimJustFinishedPlusLastFrameDuration())
    {
        statemachine->changeState("Idle");
    }
}

void KickState::Finalize()
{
}
/* #endregion */

void DuckKickState::Init()
{
    owner->canDealDamage = true;

    // play sound
    SoundManager::getInstance().playSound("mk2/punchSound.mp3");
}

void DuckKickState::Update(float deltaTime)
{
    if (owner->getAnim()->hasAnimJustFinishedPlusLastFrameDuration())
    {
        statemachine->changeState("Duck");
    }
}

void DuckKickState::Finalize()
{
}

/* #region BlockState */
void BlockState::Init()
{
    owner->stop();
}

void BlockState::Update(float deltaTime)
{
    if (!controller->block)
    {
        statemachine->changeState("Idle");
    }
}

void BlockState::Finalize()
{
}
/* #endregion */

void DuckBlockState::Init()
{
    owner->stop();
}

void DuckBlockState::Update(float deltaTime)
{
    if (!controller->block)
    {
        statemachine->changeState("Duck");
    }

    if (!controller->duck)
    {
        statemachine->changeState("Idle");
    }
}

void DuckBlockState::Finalize()
{
}

/* #region HitState */
void HitState::Init()
{
    // make sure the character will not move
    owner->stop();
    owner->canDealDamage = false;

    // play sound
    SoundManager::getInstance().playSound("hitSound.wav");

    // set timer
    if (owner->getIsAlive())
    {
        timer = 0.5f;
    }
    else
    {
        // if owner died
        timer = 0.f;
    }
}

void HitState::Update(float deltaTime)
{

    if (timer > 0.f)
    {
        timer -= deltaTime;
    }
    else
    {
        timer = 0.0f;

        // check if the owner is dead
        if (!owner->getIsAlive())
        {
            owner->setMoveVectorY(800);
            statemachine->changeState("Death");
        }
        else
        {
            statemachine->changeState("Idle");
        }
    }
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

/* #region DeathState*/
void DeathState::Init()
{
    // make sure the character will not move
    owner->stop();
    owner->canDealDamage = false;

    // play sound
    SoundManager::getInstance().playSound("ko.mp3");


    // change deltaMultiplier
    //gameManager.setDeltaTimeMultiplier(0.5f);

    // TODO: change this to opponent
    //player2->setAffectedByGravity(false);

    //player2->setPushVector({0, -250});
    //player2->setMoveVectorY(-250);
}

void DeathState::Update(float deltaTime)
{
}

void DeathState::Finalize()
{
}

/* #endregion */
