
#ifndef GBFIGHTER_BASEGAMEOBJECT_H
#define GBFIGHTER_BASEGAMEOBJECT_H

#include "../Utils/AsepriteManager.h"
#include "BaseSpriteObject.h"
#include "CollisionBox2D.h"
#include <raylib.h>

class BaseGameObject
{
public:
    BaseGameObject();
    BaseGameObject(float x, float y);
    ~BaseGameObject();

    void update(float deltaTime);
    void draw();

    // position
    void setPos(float x, float y);
    void setPos(Vector2 pos);
    Vector2 getPos();

    // scale
    void setScale(float x, float y);
    void setScale(Vector2 scale);
    Vector2 getScale();

    // sprites
    void addAnim(AsepriteAnimationFile* animfileptr2);
    AsepriteAnimationFile* getAnim();

    // hitboxes
    void addCollisionBox(std::string hitboxName);
    void removeCollisionBox(std::string hitboxName);

protected:
    Vector2 pos;
    Vector2 scale;

    // a map which holds all the sprite-objs
    std::map<std::string, BaseSpriteObject> sprites;

    AsepriteAnimationFile* animfileptr2;

    // a map which holds all the collisionbox-objs
    std::map<std::string, CollisionBox2D> collisionBoxes;
};

#endif // GBFIGHTER_BASEGAMEOBJECT_H
