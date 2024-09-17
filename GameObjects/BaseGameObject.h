
#ifndef GBFIGHTER_BASEGAMEOBJECT_H
#define GBFIGHTER_BASEGAMEOBJECT_H

#include "../Utils/AsepriteManager.h"
#include "BaseSpriteObject.h"
#include "CollisionBox2D.h"
#include <raylib.h>

class BaseGameObject
{
public:
    BaseGameObject(AsepriteManager* asepriteManager);
    BaseGameObject(AsepriteManager* asepriteManager, float x, float y);
    virtual ~BaseGameObject();

    virtual void update(float deltaTime);
    virtual void draw();

    void setObjName(std::string name);
    std::string getObjName();

    // position
    void setPos(float x, float y);
    void setPos(Vector2 pos);
    Vector2 getPos();

    // scale
    void setScale(float scale);
    float getScale();

    // sprites
    void addAnim(AsepriteAnimationFile* animfileptr);
    AsepriteAnimationFile* getAnim();
    virtual bool setCurrentFrameTag(std::string tag);
    std::string getCurrentFrameTag();

    // hitboxes
    void addCollisionBox(std::string hitboxName, float x, float y, float width, float height, Color color = BLUE);
    void removeCollisionBox(std::string hitboxName);

    // collision boxes
    std::map<std::string, CollisionBox2D>& getCollisionBoxes();

protected:
    Vector2 pos;
    float scale;
    Color color;
    bool isFlippedX;
    bool isFlippedY;
    std::string currentFrameTag;
    std::string ObjName;

    // a map which holds all the sprite-objs
    std::map<std::string, BaseSpriteObject> sprites;

    AsepriteAnimationFile* animfilePtr;
    AsepriteManager* asepriteManagerPtr;


    // a map which holds all the collisionbox-objs
    std::map<std::string, CollisionBox2D> collisionBoxes;
};

#endif // GBFIGHTER_BASEGAMEOBJECT_H
