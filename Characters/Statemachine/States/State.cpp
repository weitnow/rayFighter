#include "State.h"
#include "../../../Constants.h"
#include "../../../Utils/Input/InputHandler.h"
#include "../../../Utils/SoundManager.h"

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

void State::setOpponent(BaseCharacter* opponent)
{
    this->opponent = opponent;
}

void State::setGameState(GameState* gameState)
{
    this->gameState = gameState;
}


bool State::hasAnimationFinishedPlusLastFrameDuration()
{
    return owner->getAnimFile()->hasAnimFinishedPlusLastFrameDuration();
}

bool State::hasAnimationFinished()
{

    return owner->getAnimFile()->hasAnimFinished();
}

void State::checkTransitions(const std::vector<std::string>& allowedTransitions)
{
    for (const auto& stateName : allowedTransitions)
    {
        for (const auto& transition : commonTransitions)
        {
            if (transition.first == stateName && transition.second())
            {
                std::cout << "Transitioning from " << statemachine->getCurrentStateAsString() << " to "
                          << transition.first << std::endl;
                statemachine->changeState(stateName);
                return; // exit after first successful transition
            }
        }
    }
}

State::State(const std::string& name) : stateName(name)
{
    commonTransitions = {
        {"Special1", [this]() { return controller->special1; }},
        {"Special2", [this]() { return controller->special2; }},
        {"Special3", [this]() { return controller->special3; }},
        {"Walk", [this]() { return controller->moveLeft || controller->moveRight && !controller->duck; }},
        {"Jump", [this]() { return controller->jump; }},
        {"Duck", [this]() { return controller->duck; }},
        {"Punch", [this]() { return controller->punch; }},
        {"Kick", [this]() { return controller->kick; }},
        {"Block", [this]() { return controller->block; }},
        {"DuckPunch", [this]() { return controller->punch && controller->duck; }},
        {"DuckKick", [this]() { return controller->kick && controller->duck; }},
        {"DuckBlock", [this]() { return controller->block && controller->duck; }},
        {"JumpPunch", [this]() { return controller->punch && !controller->jump; }},
        {"Idle", [this]() { return !controller->moveLeft && !controller->moveRight && !controller->duck; }},

    };
}

/* #region IdleState */
void IdleState::Init()
{
    owner->stop(); // set moveVector.x = 0
    statemachine->changeState("Idle");
}

void IdleState::Update(float deltaTime)
{
    // checkTransitions gets checked from beginning to the end. The FIRST matching transition will be executed.
    // Order matters!
    checkTransitions({
        "Special1",
        "Special2",
        "Special3",
        "Walk",
        "Jump",
        "Duck",
        "Punch",
        "Kick",
        "Block",
    });
}

void IdleState::Finalize()
{
}

/* #endregion */

/* #region WalkState */
void WalkState::Init()
{
}

void WalkState::Update(float deltaTime)
{
    // Walk
    if (controller->moveLeft)
    {
        owner->moveLeft();
    }
    else if (controller->moveRight)
    {
        owner->moveRight();
    }

    checkTransitions({"Special1", "Special2", "Special3", "Jump", "Duck", "Idle", "Punch", "Kick", "Block"});
}

void WalkState::Finalize()
{
}
/* #endregion */

/* #region JumpState */
void JumpState::Init()
{
    alreadyJumped = false;

    // check if last state was jumpPunch
    if (owner->getStatemachine().getPreviousStateAsString() == "JumpPunch")
    {
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
    // reset the bools for next jump
    goLeft = false;
    goRight = false;
}
/* #endregion */

void JumpPunchState::Init()
{
    owner->canDealDamage = true;

    // play sound
    SoundManager::getInstance().playSound("attack1.wav");
}

void JumpPunchState::Update(float deltaTime)
{
    if (owner->getAnimFile()->hasAnimFinishedPlusLastFrameDuration())
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

    checkTransitions({"DuckPunch", "DuckKick", "DuckBlock"});
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
    SoundManager::getInstance().playSound("attack1.wav");
}

void PunchState::Update(float deltaTime)
{

    // check if animation is finished
    if (hasAnimationFinishedPlusLastFrameDuration())
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
    SoundManager::getInstance().playSound("attack1.wav");
}

void DuckPunchState::Update(float deltaTime)
{
    if (owner->getAnimFile()->hasAnimFinishedPlusLastFrameDuration())
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
    SoundManager::getInstance().playSound("attack2.wav");
}

void KickState::Update(float deltaTime)
{

    // check if animation is finished
    if (owner->getAnimFile()->hasAnimFinishedPlusLastFrameDuration())
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
    SoundManager::getInstance().playSound("attack2.wav");
}

void DuckKickState::Update(float deltaTime)
{
    if (owner->getAnimFile()->hasAnimFinishedPlusLastFrameDuration())
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
    SoundManager::getInstance().playSound("hit5.wav");

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
    SoundManager::getInstance().playSound("death3.wav");
}

void DeathState::Update(float deltaTime)
{
}

void DeathState::Finalize()
{
}

/* #endregion */
