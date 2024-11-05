#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H

#include "../Characters/BaseCharacter.h"
#include "../Characters/Statemachine/Statemachine.h"
#include "../Game/BaseState.h"
#include "../GameObjects/BaseGameObject.h"
#include <string>

class DebugInfo
{
public:
    DebugInfo(BaseState* baseState);
    ~DebugInfo();

    void draw();
    void drawGameObjectData(BaseGameObject* gameObject, const std::string& objectName, int x, int y);

    void setDebugMode(bool debugMode);

private:
    std::string currentGameObjectName;
    BaseState* baseState;
    BaseCharacter* player1;
    BaseCharacter* player2;
    int rectWidth;
    int rectHeight;
    int rectX;
    int rectY;
    Color rectColor;
    bool player1InGameObjects;

    void _drawCharacterData(BaseCharacter* character, const std::string& objectName, int x, int y);
    void _drawGameObjectData(BaseGameObject* gameObject, const std::string& objectName, int x, int y);
};

#endif //DEBUG_INFO_H
