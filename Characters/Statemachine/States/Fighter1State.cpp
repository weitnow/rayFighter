#include "Fighter1State.h"
#include "../../../Constants.h"
#include "../../../Utils/Input/InputHandler.h"
#include "../../../Utils/SoundManager.h"

void F1IdleState::Init()
{
    owner->stop(); // set moveVector.x = 0
    statemachine->changeState("Idle");
    std::cout << "F1IdleState Init" << std::endl;
}

void F1IdleState::Update(float deltaTime)
{
    std::cout << "F1IdleState Update" << std::endl;
    owner->moveRight();
}

void F1IdleState::Finalize()
{
    std::cout << "F1IdleState Finalize" << std::endl;
}

// Special1
void F1Special1State::Init()
{
    std::cout << "F1Special1State Init" << std::endl;
}

void F1Special1State::Update(float deltaTime)
{
    std::cout << "F1Special1State Update" << std::endl;
}


void F1Special1State::Finalize()
{
    std::cout << "F1Special1State Finalize" << std::endl;
}


// Special2
void F1Special2State::Init()
{
    std::cout << "F2Special1State Init" << std::endl;
}
void F1Special2State::Update(float deltaTime)
{
    std::cout << "F2Special1State Update" << std::endl;
}
void F1Special2State::Finalize()
{
    std::cout << "F2Special1State Finalize" << std::endl;
}
