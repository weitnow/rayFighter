#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../Gui/Gui.h"
#include "BaseAsepriteObject.h"
#include "BaseState.h"
#include <raylib.h>
#include <string>

// forward declarations
class AsepriteAnimationFile;
class CollisionDetection;

class GameState : public BaseState
{
public: // METHODES
    explicit GameState(Game* game);
    virtual ~GameState();
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    void Pause() override;
    void Resume() override;
    virtual void Exit() override;
    void HandleInput() override;

    //TODO: get rid of this
    unique<BaseAsepriteObject> mySpriteObject = std::make_unique<BaseAsepriteObject>(asepriteManager, 128, 80);

    BaseCharacter* createPlayer(int characterNumber, int playerNumber);

    void addGameObject(shared<BaseGameObject> gameObject, int ownerPlayerNumber); // -1 = it belongs to noone, -2 = it belongs to both, 1 = p1, 2 = p2


    [[nodiscard]] Vector2 getMiddlePointBetweenPlayers() const;
    int _getScreenPosXofObject(BaseGameObject& object);

public: // METHODES Informationprovider
    float distanceBetweenGameObjects(BaseGameObject* object1, BaseGameObject* object2);
    BaseGameObject* getClosestEnemyOf(BaseGameObject& baseGameObject,
                                      float* outDistance = nullptr,
                                      std::vector<BaseGameObject*>* outEnemies = nullptr);

public: // VARIABLES
    // <-- BaseState.h -->
    // Screen2DManager* screen2DManager;
    // BaseCharacter* player1;
    // BaseCharacter* player2;

    // <-- GameState.h -->
    int cameraX = 0; // will be updated in GameState::_updateCamera
    int cameraY = 0;


protected: // METHODES
    void _updateMiddlePointBetweenPlayers();
    void _updateIsLeftPlayer1and2();
    void _checkPushCollisionsBetweenPlayers();
    void _keepPlayersOnStage();
    void _updateCamera(bool restriction = true); // if restriction is true, the camera is restricted to the stage
    void _updateAllGameObjects(float deltaTime);
    void _updateAllBaseCharacters(float deltatime);
    void _updateHitDetection();

    void _drawAllGameObjects();
    void _drawAllBaseCharacters();

protected: // VARIABLES
    /* <-- Game.h -->
    Game* game;
    SoundManager* soundManager;
    InputHandler* inputHandler;
    AsepriteManager* asepriteManager;
    DebugInfo* debugInfo;
    float deltaTime;

    // <-- BaseState.h -->
    CharacterController* player1Controller;
    CharacterController* player2Controller;
    */

    // <-- GameState.h -->
    vector<shared<BaseCharacter>> baseCharacters;
    vector<shared<BaseGameObject>> gameObjects;
    vector<weak<BaseCharacter>> baseCharactersP1; // holds weak reference to baseCharacters
    vector<weak<BaseCharacter>> baseCharactersP2; // holds weak reference to baseCharacters
    vector<weak<BaseCharacter>> baseCharactersNoOwner; // holds weak reference to baseCharacters
    vector<weak<BaseCharacter>> baseCharactersBothOwner; // holds weak reference to baseCharacters
    vector<weak<BaseGameObject>> gameObjectsP1;   // holds weak reference to gameObjects
    vector<weak<BaseGameObject>> gameObjectsP2;   // holds weak reference to gameObjects
    vector<weak<BaseGameObject>> gameObjectsNoOwner;   // holds weak reference to gameObjects
    vector<weak<BaseGameObject>> gameObjectsBothOwner;   // holds weak reference to gameObjects
    AsepriteAnimationFile* levelAnimFile;
    Gui* gui;
    CollisionDetection* hitDetection;

    int middlePointXbetweenPlayers = 0; // will be updated in _updateMiddlePointBetweenPlayers
    int middlePointYbetweenPlayers = 0;
};

#endif
