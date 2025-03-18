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