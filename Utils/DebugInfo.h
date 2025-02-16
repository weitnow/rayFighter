#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H

#include "../Characters/BaseCharacter.h"
#include "../Characters/Statemachine/Statemachine.h"
#include "../Game/BaseState.h"
#include "../Game/GameState.h"
#include "../GameObjects/BaseGameObject.h"
#include <string>


class DebugInfo
{
public:
    DebugInfo(BaseState* baseState);
    ~DebugInfo();

    void draw();
    void setDebugMode(bool debugMode);

private:
    std::string currentGameObjectName;
    BaseState* baseState;
    GameState* gameState;
    BaseCharacter* player1;
    BaseCharacter* player2;
    Statemachine* statemachine;
    int rectWidth;
    int rectHeight;
    int rectX;
    int rectY;
    bool player1InGameObjects;

    void drawGameObjectData(BaseGameObject* gameObject, const std::string& objectName, int x, int y);
    void _drawCharacterDataInternal(BaseCharacter* character, const std::string& objectName, int x, int y);
    void _drawGameObjectDataInternal(BaseGameObject* gameObject, const std::string& objectName, int x, int y);
    void _drawDebugText(const std::string& label, const std::string& value, int x, int y);
};

#endif //DEBUG_INFO_H
