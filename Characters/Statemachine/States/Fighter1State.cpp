#include "Fighter1State.h"
#include "../../../Constants.h"
#include "../../../GameObjects/Specialmoves/Abstractclasses/Spear.h"
#include "../../../GameObjects/Specialmoves/Fireball.h"
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

// Special1 - Fireball
void F1Special1State::Init()
{
    owner->automaticallySetFrameTag = false;
    owner->setCurrentFrameTag("gbFighter-Dragonshot");
    owner->stop();
}

void F1Special1State::Update(float deltaTime)
{

    // check if animation is finished
    if (hasAnimationFinished())
    {
        // create fireball //Todo: We need a factory methode to create things like that!
        auto fireball = std::make_unique<Fireball>(owner->asepriteManagerPtr, owner->getPos().x + 20, owner->getPos().y);
        fireball->setOwnedByPlayerNumber(owner->getPlayerNumber());

        owner->addGameObjectToGameState(std::move(fireball));
        statemachine->changeState("Idle");
        owner->setCurrentFrameTag("gbFighter-Idle");
    }
}
void F1Special1State::Finalize()
{
    owner->automaticallySetFrameTag = true; // reset to default

}


// Special2 - Huricankick
void F1Special2State::Init()
{
    owner->canDealDamage = true; // allow to deal damage
    owner->automaticallySetFrameTag = false;
    owner->setCurrentFrameTag("gbFighter-A+B Move");
    owner->jump();
}
void F1Special2State::Update(float deltaTime)
{
    // check if animation is finished
    if (hasAnimationFinished())
    {
        statemachine->changeState("Idle");
        owner->setCurrentFrameTag("gbFighter-Idle");
    }
}
void F1Special2State::Finalize()
{
    owner->automaticallySetFrameTag = true; // reset to default


}



// Special3 - Spear
void F1Special3State::Init()
{
    owner->automaticallySetFrameTag = false;
    owner->setCurrentFrameTag("gbFighter-Dragonshot");
    owner->stop();
}
void F1Special3State::Update(float deltaTime)
{
    // check if animation is finished
    if (hasAnimationFinished())
    {
        // create spear //Todo: We need a factory methode to create things like that!
        auto spear = std::make_unique<Spear>(owner->asepriteManagerPtr, owner->getPos().x + 20, owner->getPos().y + 10, owner->getIsFlippedX());
        spear->setOwnedByPlayerNumber(owner->getPlayerNumber());

        owner->addGameObjectToGameState(std::move(spear));
        statemachine->changeState("Idle");
        owner->setCurrentFrameTag("gbFighter-Idle");
    }
}
void F1Special3State::Finalize()
{
    owner->automaticallySetFrameTag = true; // reset to default


}
