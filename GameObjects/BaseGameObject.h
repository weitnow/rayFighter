//
// Created by weitnow on 1/1/24.
//

#ifndef GBFIGHTER_BASEGAMEOBJECT_H
#define GBFIGHTER_BASEGAMEOBJECT_H

#include <raylib.h>
#include "BaseSpriteObject.h"
#include "CollisionBox2D.h"

class BaseGameObject {
public:
    BaseGameObject();
    BaseGameObject(float x, float y);
    ~BaseGameObject();

    void update(float deltaTime);
    void draw();

    //position
    void setPos(float x, float y);
    void setPos(Vector2 pos);
    Vector2 getPos();

    //scale
    void setScale(float x, float y);
    void setScale(Vector2 scale);
    Vector2 getScale();

    //hitboxes
    void addCollisionBox(std::string hitboxName);

protected:
    float height;
    float width;
    float scalex;
    float scaley;

    // Define the origin point for rotation (the center of the rectangle)
    Vector2 origin;

    float rotation;
    Vector2 pos;
    Vector2 scale;
    Texture2D myTexture;
    Texture2D myDebug32x32Texture;

    // Define the source rectangle (which part of myTexture should be drawn)
    Rectangle sourceRect;

    // Define the destination rectangle (used for scaling the object)
    Rectangle destRect;

    std::map<std::string, CollisionBox2D> collisionboxes;
};


#endif //GBFIGHTER_BASEGAMEOBJECT_H
