#include "State.h"


/* #region IdleState */
void IdleState::Init()
{
    std::cout << "IdleState Init" << std::endl;

    name = "Idle";
}

void IdleState::Update(float deltaTime)
{
    std::cout << "IdleState Update" << std::endl;
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

    name = "Walk";
}

void WalkState::Update(float deltaTime)
{
    std::cout << "WalkState Update" << std::endl;
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

    name = "Jump";
}

void JumpState::Update(float deltaTime)
{
    std::cout << "JumpState Update" << std::endl;
}

void JumpState::Finalize()
{
    std::cout << "JumpState Finalize" << std::endl;
}
/* #endregion */

void DuckState::Init()
{
    name = "Duck";
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
    name = "Punch";
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
    name = "Kick";
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
    name = "Block";
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
    name = "Hit";
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
    name = "Hurt";
}

void HurtState::Update(float deltaTime)
{
}

void HurtState::Finalize()
{
}
/* #endregion */
