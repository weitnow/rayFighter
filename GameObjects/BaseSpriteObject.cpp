//
// Created by weitnow on 12/7/23.
//

#include "BaseSpriteObject.h"
#include <iostream>
#include "../Constants.h"

BaseSpriteObject::BaseSpriteObject() {
    height = Constants::HEIGHT;
    width = Constants::WIDTH;
    scalex = 1.f;
    scaley = 1.f;
    pos = {Constants::X, Constants::Y};
    origin = {0, 0};
    rotation = 0.0f;
    sourceRect = {0.0f, 0.0f, 32, 32};
    destRect = {pos.x, pos.y, scaley * width, scalex * width };
    myDebug32x32Texture = LoadTexture("Assets/Graphics/debug32x32.png");
}

BaseSpriteObject::BaseSpriteObject(float x, float y) : BaseSpriteObject() {
    setPos(x, y);
}

BaseSpriteObject::BaseSpriteObject(float x, float y, float width, float height) : BaseSpriteObject(x, y) {
    this->width = width;
    this->height = height;
}

BaseSpriteObject::~BaseSpriteObject() {

}

void BaseSpriteObject::update(float deltaTime) {
    if (scalex != 1 || scaley != 1)
    {
        // then we have to update the destRect which we use for the DrawTexturePro function in the draw method of this class
        destRect.x = pos.x;
        destRect.y = pos.y;
    }

    // update hitboxes
    for(auto& pair : collisionboxes)
    {
        pair.second.update(deltaTime);
    }
}

void BaseSpriteObject::draw() {

#ifdef DEBUG
    //draw debug.png 32x32 pixel
    if(scalex == 1 && scaley == 1)
    {
        DrawTextureRec(myDebug32x32Texture, sourceRect, pos, WHITE);
    } else
    {
        DrawTexturePro(myDebug32x32Texture, sourceRect, destRect, origin, rotation, WHITE);
    }

    //draw a rectangle
    //DrawRectangle(pos.x, pos.y, width * scalex, height * scaley, Colors::getRedTransparent());

    // draw collisionboxes
    for(auto& pair : collisionboxes)
    {
        pair.second.draw();
    }


#endif

    // draw myTexture
    if(scalex == 1 && scaley == 1)
    {
        DrawTextureRec(myTexture, sourceRect, pos, WHITE);
    } else
    {
        DrawTexturePro(myTexture, sourceRect, destRect, origin, rotation, WHITE);

    }
}

void BaseSpriteObject::setPos(float x, float y) {
    pos.x = x;
    pos.y = y;

}
void BaseSpriteObject::setPos(Vector2 pos) {
    BaseSpriteObject::setPos(pos.x, pos.y);
}

Vector2 BaseSpriteObject::getPos() {
    return pos;
}

void BaseSpriteObject::setScale(float x, float y) {
    scalex = x;
    scaley = y;

    scale.x = x;
    scale.y = y;

    // updating the width and height of the destRect which is used for DrawTexturePro function in the draw methode of this class
    destRect.width = scalex * width;
    destRect.height = scaley * height;
}
void BaseSpriteObject::setScale(Vector2 scale) {
    BaseSpriteObject::setScale(scale.x, scale.y);
}

Vector2 BaseSpriteObject::getScale() {
    return scale;
}

void BaseSpriteObject::addCollisionBox(std::string hitboxName) {

    collisionboxes[hitboxName] = CollisionBox2D{};
}
