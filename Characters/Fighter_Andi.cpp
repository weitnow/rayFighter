//
// Created by weitnow on 12/24/23.
//

#include "Fighter_Andi.h"

Fighter_Andi::Fighter_Andi(int x, int y) : BaseCharacter(x, y)  {
    myTexture = LoadTexture("Assets/Graphics/gbFighter.png");
}

Fighter_Andi::~Fighter_Andi() {

}

void Fighter_Andi::draw() {
    BaseCharacter::draw();

}
