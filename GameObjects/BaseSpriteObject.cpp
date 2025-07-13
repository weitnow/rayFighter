//
// Created by weitnow on 12/7/23.
//

#include "BaseSpriteObject.h"
#include "../Constants.h"

#include <cmath>
#include <iostream>
#include <utility>

BaseSpriteObject::BaseSpriteObject()
{
    scale = 1;
    pos = {0.f, 0.f};
    rotation = 0.0f;
    color = WHITE;
    sourceRect.height = 32; // inital value = 32, needed for setpos()
    sourceRect.width = 32;  // inital value = 32, needed for setpos()

}

BaseSpriteObject::BaseSpriteObject(float x, float y) : BaseSpriteObject()
{
    setPos(x, y);
}

BaseSpriteObject::~BaseSpriteObject()
{
}

void BaseSpriteObject::update(float deltaTime)
{
    destRect.x = pos.x - origin.x;
    destRect.y = pos.y - origin.y;

    if (isMoving)
    {
        moveElapsed += deltaTime;

        float distanceSoFar = moveSpeed * moveElapsed;
        float t = moveTotalDistance > 0.0f ? distanceSoFar / moveTotalDistance : 1.0f;

        if (t >= 1.0f)
        {
            pos = moveTargetPos;
            isMoving = false;
        }
        else
        {
            float tweenedT = moveTweenFunc(t);
            pos.x = moveStartPos.x + (moveTargetPos.x - moveStartPos.x) * tweenedT;
            pos.y = moveStartPos.y + (moveTargetPos.y - moveStartPos.y) * tweenedT;
        }
    }




    /*
    // Example: rotate continuously
    rotation += 90.0f * deltaTime; // 90 degrees per second
    if (rotation >= 360.0f) rotation -= 360.0f;
    // Set origin to center for proper rotation
    origin = {destRect.width / 2.0f, destRect.height / 2.0f};
    */
}

void BaseSpriteObject::draw()
{
    //DrawTexturePro(myTexture, sourceRect, destRect, origin, rotation, color);

    DrawTexturePro(myTexture, sourceRect, destRect, origin, rotation, color);
}
void BaseSpriteObject::setPos(float x, float y)
{
    pos.x = x + sourceRect.height;
    pos.y = y + sourceRect.width;
}
void BaseSpriteObject::setPos(Vector2 pos)
{
    BaseSpriteObject::setPos(pos.x, pos.y);
}
Vector2 BaseSpriteObject::getPos()
{
    return {pos.x - std::abs(sourceRect.width), pos.y - std::abs(sourceRect.height)};
}


void BaseSpriteObject::moveTowards(Vector2 target, float speed, std::function<float(float)> tweenFunc)
{
    isMoving = true;
    moveStartPos = pos;
    moveTargetPos = target;
    moveElapsed = 0.0f;
    moveSpeed = speed;
    moveTweenFunc = std::move(tweenFunc);

    float dx = target.x - pos.x;
    float dy = target.y - pos.y;
    moveTotalDistance = std::sqrtf(dx * dx + dy * dy);
}

void BaseSpriteObject::loadTexture(const std::string& texturePath)
{
    myTexture = LoadTexture(texturePath.c_str());
    sourceRect = {
        0.f,
        0.f,
        static_cast<float>(myTexture.width),
        static_cast<float>(myTexture.height) // <- fix here
    };

    // Adjust destRect size if texture was loaded after scale was set
    destRect.width = scale * sourceRect.width;
    destRect.height = scale * sourceRect.height;

    // Update origin after loading new texture
    origin = {destRect.width / 2.0f, destRect.height / 2.0f};
}
void BaseSpriteObject::unloadTexture()
{
    UnloadTexture(myTexture);
    myTexture.id = 0; // mark it as unloaded
    destRect.height = 32;
    destRect.width = 32;
}


void BaseSpriteObject::setScale(int scaleLevel)
{
    scale = scaleLevel;

    // updating the width and height of the destRect which is used for DrawTexturePro function in the draw methode of this class
    destRect.width = scale * sourceRect.width;
    destRect.height = scale * sourceRect.height;


}


int BaseSpriteObject::getScale()
{
    return scale;
}
void BaseSpriteObject::setIsFlippedX(bool flipX)
{
    isFlippedX = flipX;
    if (this->isFlippedX)
    {
        sourceRect.width = -sourceRect.width;
        sourceRect.height = sourceRect.height;
        destRect.width = -destRect.width;
        destRect.height = destRect.height;
    }
    else
    {
        sourceRect.width = std::abs(sourceRect.width);
        sourceRect.height = sourceRect.height;
        destRect.width = std::abs(destRect.width);
        destRect.height = destRect.height;
    }
}
void BaseSpriteObject::setIsFlippedY(bool flipY)
{
    isFlippedY = flipY;
    if (this->isFlippedY)
    {
        sourceRect.width = sourceRect.width;
        sourceRect.height = -sourceRect.height;
        destRect.width = destRect.width;
        destRect.height = -destRect.height;
    }
    else
    {
        sourceRect.width = sourceRect.width;
        sourceRect.height = std::abs(sourceRect.height);
        destRect.width = destRect.width;
        destRect.height = std::abs(destRect.height);
    }
}
bool BaseSpriteObject::getIsFlippedX()
{
    return isFlippedX;
}
bool BaseSpriteObject::getIsFlippedY()
{
    return isFlippedY;
}
void BaseSpriteObject::setRotation(int rotation)
{
    this->rotation = static_cast<float>(rotation);
}
int BaseSpriteObject::getRotation()
{
    return static_cast<int>(rotation);
}
void BaseSpriteObject::setColor(Color color)
{
    this->color = color;
}
