#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H

#include "../Characters/BaseCharacter.h"
#include "../Characters/Statemachine/Statemachine.h"
#include "../GameObjects/BaseGameObject.h"
#include "Core.h"
#include "GameManager.h"
#include <string>

class DebugInfo
{
public:
    DebugInfo();
    virtual ~DebugInfo();

    void addGameObject(const std::string& name, BaseGameObject* gameObject);
    void removeGameObject(std::string& name);
    bool showNextGameObject();
    void update(float deltaTime);
    void draw();
    void drawGameObjectData(BaseGameObject* gameObject, const std::string& objectName, int x, int y);

protected:
    Dictionary<std::string, BaseGameObject*> gameObjects;
    std::string currentGameObjectName;
    int rectWidth;
    int rectHeight;
    int rectX;
    int rectY;
    Color rectColor;
    bool player1InGameObjects;
};

#endif //DEBUG_INFO_H
