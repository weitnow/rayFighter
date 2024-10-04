#include "BaseCharacter.h"
#include "../Constants.h"
#include "Statemachine/Statemachine.h"

BaseCharacter::BaseCharacter(AsepriteManager* asepriteManager, float x, float y)
    : BaseGameObject(asepriteManager, x, y), isOnGround(false), animFileName("gbFighter"), isLeft(true),
      playerNumber(-1), statemachine(std::make_unique<Statemachine>(*this)), currentState("Idle")
{
    statemachine->setOwner(this);

#ifdef DEBUG
    std::cout << "BaseCharacter created" << std::endl;
#endif
}


BaseCharacter::~BaseCharacter()
{
#ifdef DEBUG
    std::cout << "BaseCharacter destroyed" << std::endl;
#endif
}

void BaseCharacter::update(float deltaTime)
{
    if (scale != 1)
    {
        // TODO: Implement scale function
    }


    // UPDATE THE POSITION
    this->setPos(this->getPos().x + (moveVector.x + pushVector.x) * deltaTime,
                 this->getPos().y + (moveVector.y + pushVector.y) * deltaTime);


    // REDUCE PUSH VECTOR
    _reducePushVector(deltaTime);

    //APPLY GRAVITY
    if (affectedByGravity)
        _applyGravity(deltaTime);

    // UPDATE THE STATE
    statemachine->update(deltaTime);

    // KEEP THE CHARACTER ON THE STAGE
    _keepOnStage();

    // UPDATE THE COLLISION BOXES
    for (auto& pair : collisionBoxes)
    {
        pair.second.update(deltaTime);
        pair.second.setObjPos(getPos().x, getPos().y);
    }

    // UPDATE THE SPRITE
    if (statemachine->getCurrentStateAsString() == "No current state")
    {
        setCurrentFrameTag(animFileName + "-Idle");
    }
    else if (currentState != statemachine->getCurrentStateAsString())
    {
        currentState = statemachine->getCurrentStateAsString();
        setCurrentFrameTag(animFileName + "-" + statemachine->getCurrentStateAsString());
    }
    // update the member variables from the animationfile
    _updateMemberVariables();

    // check if this->animfileptr is not nullptr - if its not, then update the animation
    if (animfilePtr != nullptr)
    {
        animfilePtr->update(deltaTime);
    }
}


void BaseCharacter::draw()
{

    BaseGameObject::draw();
}

void BaseCharacter::moveLeft()
{

    this->moveVector.x = -walkingSpeed;
}

void BaseCharacter::moveRight()
{

    this->moveVector.x = +walkingSpeed;
}

void BaseCharacter::stop()
{
    this->moveVector.x = 0;
}

void BaseCharacter::jump()
{
    if (this->isOnGround)
    {
        this->moveVector.y = -jumpForce;
        this->isOnGround = false;
    }
}

void BaseCharacter::duck()
{
}

void BaseCharacter::punch()
{
}

void BaseCharacter::setIsLeft(bool isLeft)
{
    this->isLeft = isLeft;
    // if the character is left, flip the sprite
    // TODO: refactor this methode and calculate the sprite position
    if (isLeft)
    {
        this->isFlippedX = false;
    }
    else
    {
        this->isFlippedX = true;
    }
}

bool BaseCharacter::getIsLeft()
{
    return isLeft;
}

void BaseCharacter::setPlayerNumber(int playerNumber)
{
    if (playerNumber != 1 && playerNumber != 2)
    {
        throw std::invalid_argument("Player number must be 1 or 2");
    }

    // check if the player has a ObjName
    if (this->getObjName().empty())
    {
        this->setObjName("Player" + std::to_string(playerNumber));
    }
    this->playerNumber = playerNumber;
}

int BaseCharacter::getPlayerNumber()
{
    return playerNumber;
}


void BaseCharacter::addController(CharacterController* controller)
{
    if (controller)
    {
        this->controller = controller;
    }
    else
    {
        throw std::runtime_error("Controller is nullptr");
    }
}

CharacterController* BaseCharacter::getController()
{
    return controller;
}


bool BaseCharacter::setCurrentFrameTag(std::string tag)
{
    // set animFilename to the first part of the tag for example "gbFighter-Idle" -> "gbFighter"
    animFileName = tag.substr(0, tag.find("-"));
    // this is needed to set the correct animation when changing states by calling changeState()

    // if the animation is already playing, return false, otherwise return true
    return BaseGameObject::setCurrentFrameTag(tag);
}


std::string BaseCharacter::getCurrentState()
{
    return currentState;
}

bool BaseCharacter::getIsOnGround()
{
    return isOnGround;
}

Vector2 BaseCharacter::getMoveVector()
{
    return moveVector;
}

Statemachine& BaseCharacter::getStatemachine()
{
    if (statemachine)
    {
        return *statemachine;
    }
    else
    {
        throw std::runtime_error("Statemachine is nullptr");
    }
}

void BaseCharacter::_applyGravity(float deltaTime)
{
    //if character is on the ground, stop falling
    if (this->getPos().y > Constants::BASELINE || isOnGround)
    {
        this->isOnGround = true;
        this->setPos(this->getPos().x, Constants::BASELINE);
        this->moveVector.y = 0;
    }
    else if (this->getPos().y < Constants::BASELINE || !isOnGround)
    {
        this->isOnGround = false;
        this->moveVector.y += Global::gravity * deltaTime;
    }
}

void BaseCharacter::_keepOnStage()
{
    // KEEP THE CHARACTER IN THE WINDOW
    // check if the character is out of bounds
    if (this->getPos().x < 0)
    {
        this->setPos(0, this->getPos().y);
    }
    else if (this->getPos().x > Constants::BACKGROUND_WIDTH - Constants::PLAYER_WIDTH)
    {
        this->setPos(Constants::BACKGROUND_WIDTH - Constants::PLAYER_WIDTH, this->getPos().y);
    }
}
