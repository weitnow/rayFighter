//
// Created by weitnow on 12/7/23.
//

#include "BaseCharacter.h"


BaseCharacter::BaseCharacter() {
    BaseGameObject();
}

BaseCharacter::BaseCharacter(int x, int y) {
    BaseGameObject(x, y);
}


BaseCharacter::~BaseCharacter() {

}

void BaseCharacter::update(float deltaTime) {
    BaseGameObject::update(deltaTime);
}

void BaseCharacter::draw() {
    BaseGameObject::draw();
}


