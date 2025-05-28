#include "BaseCharacter.h"
#include "../Constants.h"
#include "../Utils/Input/CharacterController.h"
#include "Statemachine/Statemachine.h"

BaseCharacter::BaseCharacter(AsepriteManager* asepriteManager, float x, float y)
    : BaseGameObject(asepriteManager, x, y), isOnGround(false), animFileName("gbFighter"), isLeft(true),
      playerNumber(-1), statemachine(nullptr), currentState("Idle"), canDealDamage(true), controller(nullptr),
      powerLevel(0), maxPowerLevel(0)
{
    affectedByGravity =
        true; // needs to be set here, because in the initializer list of basegameobject it is set to false
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::init() // will be called by the createPlayer function in GameState
{
    statemachine = std::make_unique<Statemachine>(this);
}

void BaseCharacter::update(float deltaTime)
{
    if (scale != 1)
    {
        // TODO: Implement scale function
    }

    // UPDATE COLLISION BOXES
    _updateCollisionBoxes(deltaTime);

    // UPDATE THE POSITION
    this->setPos(this->getPos().x + (moveVector.x + pushVector.x) * deltaTime,
                 this->getPos().y + (moveVector.y + pushVector.y) * deltaTime);

    // REDUCE PUSH VECTOR
    _reducePushVector(deltaTime);

    //APPLY GRAVITY
    if (affectedByGravity)
    {
        _applyGravity(deltaTime);
    }

    // UPDATE THE STATE
    statemachine->update(deltaTime);

    // UPDATE THE SPRITE
    if (automaticallySetFrameTag)
    {
        if (statemachine->getCurrentStateAsString() == "No current state")
        {
            setCurrentFrameTag(animFileName + "-Idle");
        }
        else if (currentState != statemachine->getCurrentStateAsString())
        {
            currentState = statemachine->getCurrentStateAsString();
            setCurrentFrameTag(animFileName + "-" + statemachine->getCurrentStateAsString());
        }
    }

    // update the member variables from the animationfile
    _updateMemberVariables();
    _updateCharacterController();

    // check if this->animfileptr is not nullptr - if its not, then update the animation
    if (animfilePtr != nullptr)
    {
        animfilePtr->update(deltaTime);
    }
}

const std::vector<SpecialMove>& BaseCharacter::getSpecialMoves() const
{
    return specialMoves;
}


void BaseCharacter::draw()
{

    BaseGameObject::draw();
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

void BaseCharacter::takeDamage(float damage, CollisionBox2D* hitbox)
{


    BaseGameObject::takeDamage(damage, hitbox);

    statemachine->changeState("Hit");
}

void BaseCharacter::setIsLeft(bool isLeft)
{
    this->isLeft = isLeft;

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

void BaseCharacter::setMoveVectorY(int yValue)
{
    isOnGround = false;
    BaseGameObject::setMoveVectorY(yValue);
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
    if (!controller)
    {
        throw std::runtime_error("Failed to add controller: provided controller is nullptr.");
    }

    this->controller = controller; // Optionally manage lifecycle if necessary.
}

CharacterController* BaseCharacter::getController()
{
    if (controller == nullptr)
    {
        std::cout << "BaseCharacter.cpp - warning: getController() returned a nullptr" << std::endl;
    }

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

void BaseCharacter::setMaxPowerLevel(int maxPowerLevel)
{
    this->maxPowerLevel = maxPowerLevel;
}

int BaseCharacter::getMaxPowerLevel()
{
    return maxPowerLevel;
}

void BaseCharacter::setPowerLevel(int powerLevel)
{
    if (powerLevel < 0 || powerLevel > maxPowerLevel)
    {
        throw std::invalid_argument("Power level must be between 0 and maxPowerLevel");
    }
    this->powerLevel = powerLevel;
}

int BaseCharacter::getPowerLevel()
{
    return powerLevel;
}

void BaseCharacter::_applyGravity(float deltaTime)
{
    //if character is on the ground, stop falling
    if (this->getPos().y > Constants::BASELINE - 5 || isOnGround)
    {
        this->isOnGround = true;
        this->setPos(this->getPos().x, Constants::BASELINE - 5);
        this->moveVector.y = 0;
    }
    else if (this->getPos().y < Constants::BASELINE - 5 || !isOnGround)
    {
        this->isOnGround = false;
        this->moveVector.y += Global::gravity * deltaTime;
    }
}

void BaseCharacter::_updateCharacterController()
{
    if (controller == nullptr)
        return;

    controller->isLeft = isLeft;
}
