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
    pos = {0.f, 0.f};
    origin = {0, 0};
    rotation = 0.0f;
    destRect = {pos.x, pos.y, scale.y * sourceRect.height, scale.x * sourceRect.width};
    myDebug32x32Texture = LoadTexture("Assets/Graphics/debug32x32.png"); //Raylib function
    loadTexture("Assets/Graphics/debug32x32.png");                       //class method
}

BaseSpriteObject::BaseSpriteObject(float x, float y, const std::string& texturePath) : BaseSpriteObject()
{
    setPos(x, y);
    loadTexture(texturePath);
    std::cout << "calling BaseSpriteObj with " << texturePath << std::endl;
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

void BaseSpriteObject::loadTexture(const std::string& texturePath)
{
    myTexture = LoadTexture(texturePath.c_str());
    sourceRect = {0.0f, 0.0f, static_cast<float>(myTexture.width), static_cast<float>(myTexture.width)};
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
