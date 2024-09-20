#include "State.h"
#include "../../Utils/GameManager.h"
#include "../../Utils/InputHandler.h"

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
    stateName = "Idle";
}

void IdleState::Update(float deltaTime)
{
    // allowed transitions
    // walk, jump, duck, punch, kick, block, hit, hurt

    if (controller->moveLeft || controller->moveRight)
    {
        statemachine->changeState("Walk");
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

    stateName = "Walk";

    statemachine->changeState("Walk");
}

void WalkState::Update(float deltaTime)
{
    if (controller->moveLeft)
    {
        owner->moveLeft();
    }
    else if (controller->moveRight)
    {
        owner->moveRight();
    }
    else
    {
        statemachine->changeState("Idle");
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

    stateName = "Jump";
}

void JumpState::Update(float deltaTime)
{
}

void JumpState::Finalize()
{
    std::cout << "JumpState Finalize" << std::endl;
}
/* #endregion */

void DuckState::Init()
{
    stateName = "Duck";
}

/* #region DuckState */
void DuckState::Update(float deltaTime)
{
}

void DuckState::Finalize()
{
}
/* #endregion */

/* #region PunchState */
void PunchState::Init()
{
    stateName = "Punch";
}

void PunchState::Update(float deltaTime)
{
}

void PunchState::Finalize()
{
}
/* #endregion */

/* #region KickState */
void KickState::Init()
{
    stateName = "Kick";
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
    stateName = "Block";
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
    stateName = "Hit";
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
    stateName = "Hurt";
}

void HurtState::Update(float deltaTime)
{
}

void HurtState::Finalize()
{
}
/* #endregion */
