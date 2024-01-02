//
// Created by weitnow on 1/1/24.
//

#include "CollisionBox2D.h"
#include "../Constants.h"

CollisionBox2D::CollisionBox2D() {

    width = 16.0f;
    height = 16.0f;
    myRectangle = {0, 0, width, height};
    color = Colors::getRedTransparent();
}

CollisionBox2D::~CollisionBox2D() {

}

void CollisionBox2D::update(float deltaTime) {
    myRectangle.x = pos.x;
    myRectangle.y = pos.y;
}

void CollisionBox2D::draw() {
    DrawRectangleRec(myRectangle, color);
}

void CollisionBox2D::setPos(float x, float y) {
    pos.x = x;
    pos.y = y;
}
