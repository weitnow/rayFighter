#include "TeleportState.h"
#include "../../../../Constants.h"
#include "../../../../Utils/Input/InputHandler.h"
#include "../../../../Utils/SoundManager.h"

void TeleportState::Init()
{
    owner->stop(); // set moveVector.x = 0
    statemachine->changeState("Idle");
    std::cout << "TeleportState Init" << std::endl;
}

void TeleportState::Update(float deltaTime)
{
   std::cout << "TeleportState Update" << std::endl;
   owner->moveRight();
}

void TeleportState::Finalize()
{
    std::cout << "TeleportState Finalize" << std::endl;
}