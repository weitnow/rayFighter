
#ifndef GBFIGHTER_BASEGAMEOBJECT_H
#define GBFIGHTER_BASEGAMEOBJECT_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/Core.h"
#include "CollisionBox2D.h"
#include <raylib.h>

// Forward declaration of GameState
class GameState;

// Using directive to shorten the type name
using CollisionMap = Dictionary<std::string, List<CollisionBox2D>>;

class BaseGameObject
{
public:
    BaseGameObject(AsepriteManager* asepriteManager);
    BaseGameObject(AsepriteManager* asepriteManager, float x, float y);
    virtual ~BaseGameObject();

    virtual void init();

    virtual void update(float deltaTime);
    virtual void draw();

    virtual void takeDamage(float damage = 1.f);
    virtual void takeDamage(float damage, CollisionBox2D* hitbox);

    virtual void onYouGotHit(List<CollisionBox2D*>& hitboxesThatHit, List<CollisionBox2D*>& hurtboxesThatWereHit, BaseGameObject& otherGameObject);
    virtual void onYouHit(List<CollisionBox2D*>& hitboxesThatHit, List<CollisionBox2D*>& hurtboxesThatWereHit, BaseGameObject& otherGameObject);

    int getMaxLife();
    void setMaxLife(int maxLife);

    int getCurrentLife();
    void setCurrentLife(int currentLife);

    bool getIsAlive();
    bool getIsActive();
    bool getShouldDestroy();

    void setObjName(std::string name);
    std::string getObjName();

    // sprites
    void addAnim(AsepriteAnimationFile* animfileptr);
    AsepriteAnimationFile* getAnimFile();
    virtual bool setCurrentFrameTag(std::string tag);
    std::string getCurrentFrameTag();

    void setDrawShadow(bool drawShadow);
    void setShadowGroundLevel(int groundlevel);
    void setShadowSize(float size);
    void setShadowColor(Color color);
    void setShadowOpacity(float opacity);

    void setIsFlippedX(bool isFlippedX);
    bool getIsFlippedX();

    // collision boxes
    List<CollisionBox2D> getPushBoxes();
    List<CollisionBox2D> getHitBoxes();
    List<CollisionBox2D> getHurtBoxes();
    List<CollisionBox2D> getThrowBoxes();

    bool canDealDamage; // hitdetection will only work if this is true, it will be set to false by the CollisionDetection-System, after a hit has been registered

    // position
    void setPos(float x, float y);
    void setPos(Vector2 pos);
    virtual Vector2 getPos() const;
    void resetPos(); // sets the object to the orginal position where it was instantiated

    //pushVector
    void setPushVector(Vector2 pushVector);
    Vector2 getPushVector();
    void resetPushVector();

    //moveVector
    virtual void setMoveVector(Vector2 moveVector);
    virtual void setMoveVectorY(int yValue);
    virtual void setMoveVectorX(int xValue);

    //move object indirectly by set Speed
    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveUp();
    virtual void moveDown();
    virtual void stop();
    virtual void setMoveSpeed(int speed);

    //gravity
    void setAffectedByGravity(bool affectedByGravity);

    // scale
    void setScale(float scale);
    float getScale();

    // HitBoxes
    void addCollisionBoxForFrame(const std::string frameTag,
                                 int frameNumber,
                                 CollisionBoxType collisionBoxType,
                                 HurtboxType hurtboxType,
                                 bool isActive,
                                 float offsetX,
                                 float offsetY,
                                 float width,
                                 float height);

    void addCollisionBoxForFrame(const std::string frameTag,
                                 int frameNumber,
                                 CollisionBoxType collisionBoxType,
                                 bool isActive,
                                 float offsetX,
                                 float offsetY,
                                 float width,
                                 float height);

    void setGameState(GameState* gameState);

    void addGameObjectToGameState(std::unique_ptr<BaseGameObject> gameObject); //used for fireball etc.

    AsepriteManager* asepriteManagerPtr;


protected:
    Vector2 orginalPos; // the original position of the object as it was created - used for reseting the object
    Vector2 pos;        // calculated in the update method
    Vector2 moveVector; // (x,y) used to walk and jump
    Vector2 pushVector; // (x,y) used by setPushVector and reduced by _reducePushVector in update methode
    float moveSpeed = 60.f;
    float scale;
    Color color;
    bool isFlippedX;
    bool isFlippedY;
    std::string currentFrameTag; // for example "gbFighter-Idle"
    std::string ObjName;         // for example "Andy"
    bool isActive;               // if isActive is false, object is NOT updated or drawn
    bool isAlive;                // if life is < 0 takeDamage will set isAlive = false
    bool shouldDestroy;          // if shouldDestroy is true, objects gets removed from the game (except p1 or p2)
    bool isInvincible;
    int getDurationCurrentFrame; // Duration of the current frame in milliseconds
    int currentFrame;            // current frame of the animation
    int minFrame;                // min frame of the animation
    int maxFrame;                // max frame of the animation
    bool hasAnimFinished;        // true if the animation has just finished
    int currentFrameAbsolut;     // current frame number of the animation - min frame

    int maxLife;
    int currentLife;

    // shadow
    bool drawShadow;
    int shadowGroundLevel = 125;
    float shadowSize = 1.f;
    Color shadowColor = BLACK;
    float shadowOpacity = 0.2f;

    float _invincibleCounter;
    float invincibleTime;
    bool affectedByGravity;

    // CollisionMap holds collisionBoxes per frame like this: collisionBoxesPerFrame["gbFighter-Idle"][0] = List<CollisionBox2D>
    CollisionMap hitBoxesPerFrame;
    CollisionMap hurtBoxesPerFrame;
    CollisionMap pushBoxesPerFrame;
    CollisionMap throwBoxesPerFrame;

    AsepriteAnimationFile* animfilePtr;

    GameState* gameState;

    // member functions
    virtual void _reducePushVector(float deltaTime);
    virtual void _applyGravity(float deltaTime);
    void _updateMemberVariables(); // update member variables from the animationfile
    void _drawShadow(int groundLevel = Constants::BASELINE + 23,
                     float shadowSize = 1,
                     Color color = BLACK,
                     float shadowOpacity = 0.2f);
    void _updateCollisionBoxes(float deltaTime);
    void _drawCollisionBoxes();
    void _addCollisionBoxForFrameInternal(std::string frameTagName,
                                          int offsetX,
                                          int offsetY,
                                          int width,
                                          int height,
                                          float hitboxOwnerWith,
                                          CollisionBoxType collisionBoxType,
                                          HurtboxType hurtboxType,
                                          bool isActive);

    List<CollisionBox2D> _checkIfCollisionMapHasCollisionBoxesAndReturnList(const std::string& currentFrameTag,
                                                                            const int currentFrameAbsolut,
                                                                            CollisionBoxType collisionBoxType);
};

#endif // GBFIGHTER_BASEGAMEOBJECT_H
