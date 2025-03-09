#include "Barrel.h"

Barrel::Barrel(AsepriteManager* asepriteManager, float x, float y) : BaseGameObject(asepriteManager, x, y)
{
}

Barrel::~Barrel()
{
}

void Barrel::update(float deltaTime)
{
    BaseGameObject::update(deltaTime);

    // stop hit animation and set back to idle
    if (currentFrameTag == "barrel-Hit" && this->getAnim()->hasAnimJustFinished())
    {
        setCurrentFrameTag("barrel-Idle");
    }

    // timer
    if (_invincibleCounter > 0.f)
    {
        _invincibleCounter -= deltaTime;
    }
    else
    {
        isInvincible = false;
        _invincibleCounter = 0.f;
    }

    if (currentLife <= 0 && isAlive)
    {
        isAlive = false;
        setPushVector({300, -150});
        setCurrentFrameTag("barrel-Destroyed");
    }
}

void Barrel::takeDamage(float damage)
{
    if (!isInvincible)
    {
        setPushVector({150, -50});
        setCurrentFrameTag("barrel-Hit");
        std::cout << "Barrel::takeDamage -> " << ObjName << " took " << damage << " damage." << std::endl;
        currentLife -= damage;
        isInvincible = true;
        _invincibleCounter = invincibleTime;
    }
}

void Barrel::init()
{
}

void Barrel::_reducePushVector(float deltaTime)
{
    BaseGameObject::_reducePushVector(deltaTime);
}
