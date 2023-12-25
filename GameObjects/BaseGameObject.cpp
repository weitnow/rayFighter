//
// Created by weitnow on 12/7/23.
//

#include "BaseGameObject.h"
#include <iostream>
#include "../Constants.h"

BaseGameObject::BaseGameObject() {
    height = Constants::HEIGHT;
    width = Constants::WIDTH;
    scalex = 1.f;
    scaley = 1.f;
    pos = {Constants::X, Constants::Y};
    origin = { width/2, height/2};
    rotation = 0.0f;
    sourceRect = {0.0f, 0.0f, 32, 32};
    destRect = {pos.x, pos.y, scaley * width, scalex * width };
}

BaseGameObject::BaseGameObject(int x, int y) : BaseGameObject() {
    setPos(x, y);
}

BaseGameObject::BaseGameObject(int x, int y, float width, float height) : BaseGameObject(x, y) {
    this->width = width;
    this->height = height;
}

BaseGameObject::~BaseGameObject() {

}

void BaseGameObject::update(float deltaTime) {
    if (scalex != 1 || scaley != 1)
    {
        // then we have to update the destRect which we use for the DrawTexturePro function in the draw method of this class
        destRect.x = pos.x;
        destRect.y = pos.y;
    }
}

void BaseGameObject::draw() {

#ifdef DEBUG
    //draw a rectangle
    DrawRectangle(pos.x, pos.y, width, height, RED);
#endif

    if(scalex == 1 && scaley == 1)
    {
        DrawTextureRec(myTexture, sourceRect, pos, WHITE);
    } else
    {
        DrawTexturePro(myTexture, sourceRect, destRect, origin, rotation, WHITE);
    }

}

void BaseGameObject::setPos(int x, int y) {
    pos.x = x;
    pos.y = y;

}

Vector2 BaseGameObject::getPos() {
    return pos;
}

void BaseGameObject::setScale(int x, int y) {
    scalex = x;
    scaley = y;

    scale.x = x;
    scale.y = y;

    // updating the width and height of the destRect which is used for DrawTexturePro function in the draw methode of this class
    destRect.width = scalex * width;
    destRect.height = scaley * height;

}

Vector2 BaseGameObject::getScale() {
    return scale;
}
