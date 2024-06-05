//
// Created by weitnow on 12/7/23.
//

#include "BaseCharacter.h"


BaseCharacter::BaseCharacter() : BaseSpriteObject() {

}

BaseCharacter::BaseCharacter(float x, float y) : BaseSpriteObject(x, y) {

}


BaseCharacter::~BaseCharacter() {

}

void BaseCharacter::update(float deltaTime) {
    BaseSpriteObject::update(deltaTime);
}

void BaseCharacter::draw() {
    BaseSpriteObject::draw();
}


