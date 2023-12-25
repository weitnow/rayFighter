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

BaseGameObject::BaseGameObject(int x, int y) {

}

BaseGameObject::BaseGameObject(int x, int y, float with, float height) : BaseGameObject(x, y) {

}

BaseGameObject::~BaseGameObject() {

}

void BaseGameObject::update() {
    pos.x ++;
}

void BaseGameObject::draw() {

    //draw a rectangle
    DrawRectangle(this->pos.x, this->pos.y, 50, 50, RED);


    if(scalex == 1 && scaley == 1)
    {
        DrawTextureRec(myTexture, sourceRect, pos, WHITE);
        std::cout << "normal draw mode"<< std::endl;
    } else
    {
        DrawTexturePro(myTexture, sourceRect, destRect, origin, rotation, WHITE);
        std::cout << "scaled draw mode"<< std::endl;
    }

}

void BaseGameObject::setPos(int x, int y) {
    this->pos.x = x;
    this->pos.y = y;

}

Vector2 BaseGameObject::getPos() {
    return pos;
}

void BaseGameObject::setScale(int x, int y) {
    scalex = x;
    scaley = y;
    this->scale.x = x;
    this->scale.y = y;
}

Vector2 BaseGameObject::getScale() {
    return scale;
}
