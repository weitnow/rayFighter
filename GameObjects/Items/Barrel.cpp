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

    if (life <= 0)
    {
        isAlive = false;
    }
}

void Barrel::takeDamage(float damage)
{
    if (!isInvincible)
    {
        setCurrentFrameTag("barrel-Hit");
        std::cout << "Barrel::takeDamage -> " << ObjName << " took " << damage << " damage." << std::endl;
        life -= damage;
        isInvincible = true;
        _invincibleCounter = invincibleTime;
    }
}

void Barrel::_reducePushVector(float deltaTime)
{
}
