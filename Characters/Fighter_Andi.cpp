//
// Created by weitnow on 12/24/23.
//

#include "Fighter_Andi.h"

Fighter_Andi::Fighter_Andi(float x, float y) : BaseCharacter(x, y)  {
    myTexture = LoadTexture("Assets/Graphics/gbFighter.png");

}

Fighter_Andi::~Fighter_Andi() {

}

void Fighter_Andi::update(float deltaTime) {
    //pos.x++;
    BaseCharacter::update(deltaTime);
}

void Fighter_Andi::draw() {
    BaseCharacter::draw();

}
