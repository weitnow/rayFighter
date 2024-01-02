//
// Created by weitnow on 1/1/24.
//

#include "BaseGameObject.h"

#include "../Constants.h"

BaseGameObject::BaseGameObject() {
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

BaseGameObject::BaseGameObject(float x, float y) : BaseGameObject() {
    setPos(x, y);
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

    // update hitboxes
    for(auto& pair : collisionboxes)
    {
        pair.second.update(deltaTime);
    }
}

void BaseGameObject::draw() {

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

void BaseGameObject::setPos(float x, float y) {
    pos.x = x;
    pos.y = y;

}
void BaseGameObject::setPos(Vector2 pos) {
    BaseGameObject::setPos(pos.x, pos.y);
}

Vector2 BaseGameObject::getPos() {
    return pos;
}

void BaseGameObject::setScale(float x, float y) {
    scalex = x;
    scaley = y;

    scale.x = x;
    scale.y = y;

    // updating the width and height of the destRect which is used for DrawTexturePro function in the draw methode of this class
    destRect.width = scalex * width;
    destRect.height = scaley * height;
}
void BaseGameObject::setScale(Vector2 scale) {
    BaseGameObject::setScale(scale.x, scale.y);
}

Vector2 BaseGameObject::getScale() {
    return scale;
}

void BaseGameObject::addCollisionBox(std::string hitboxName) {

    collisionboxes[hitboxName] = CollisionBox2D{};
}
