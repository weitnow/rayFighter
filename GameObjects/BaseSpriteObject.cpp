//
// Created by weitnow on 12/7/23.
//

#include "BaseSpriteObject.h"
#include "../Constants.h"
#include <iostream>

BaseSpriteObject::BaseSpriteObject()
{
    scale.x = 1.f;
    scale.y = 1.f;
    pos = {Constants::X, Constants::Y};
    origin = {0, 0};
    rotation = 0.0f;
    sourceRect = {0.0f, 0.0f, 32, 32};
    destRect = {pos.x, pos.y, scale.y * sourceRect.height, scale.x * sourceRect.width};
    myDebug32x32Texture = LoadTexture("Assets/Graphics/debug32x32.png");
    myTexture =
        LoadTexture("Assets/Graphics/debug32x32.png"); // default texture, will be overwritten by the inheriting class
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
    if (scale.x != 1 || scale.y != 1)
    {
        // then we have to update the destRect which we use for the DrawTexturePro function in the draw method of this class
        destRect.x = pos.x;
        destRect.y = pos.y;
    }
}

void BaseSpriteObject::draw()
{
    // draw myTexture
    if (scale.x == 1 && scale.y == 1)
    {
        DrawTextureRec(myTexture, sourceRect, pos, WHITE);
    }
    else
    {
        DrawTexturePro(myTexture, sourceRect, destRect, origin, rotation, WHITE);
    }

    if (Global::debugMode)
    {
        //draw debug.png 32x32 pixel
        if (scale.x == 1 && scale.y == 1)
        {
            DrawTextureRec(myDebug32x32Texture, sourceRect, pos, WHITE);
        }
        else
        {
            DrawTexturePro(myDebug32x32Texture, sourceRect, destRect, origin, rotation, WHITE);
        }
    }
}

void BaseSpriteObject::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}
void BaseSpriteObject::setPos(Vector2 pos)
{
    BaseSpriteObject::setPos(pos.x, pos.y);
}

Vector2 BaseSpriteObject::getPos()
{
    return pos;
}

void BaseSpriteObject::setScale(float x, float y)
{
    scale.x = x;
    scale.y = y;

    // updating the width and height of the destRect which is used for DrawTexturePro function in the draw methode of this class
    destRect.width = scale.x * sourceRect.width;
    destRect.height = scale.y * sourceRect.height;
}
void BaseSpriteObject::setScale(Vector2 scale)
{
    BaseSpriteObject::setScale(scale.x, scale.y);
}

Vector2 BaseSpriteObject::getScale()
{
    return scale;
}
