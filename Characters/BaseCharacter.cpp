//
// Created by weitnow on 12/7/23.
//

#include "BaseCharacter.h"


BaseCharacter::BaseCharacter() {
    this->pos.x = 0;
    this->pos.y = 0;
    this->height = 50;
    this->width = 50;
}

BaseCharacter::BaseCharacter(int x, int y) {
    this->pos.x = x;
    this->pos.y = y;
    this->height = 50;
    this->width = 50;
}

BaseCharacter::~BaseCharacter() {

}

void BaseCharacter::update() {
    BaseGameObject::update();
}

void BaseCharacter::draw() {
    BaseGameObject::draw();
}


