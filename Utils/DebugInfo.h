#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H

#include "../GameObjects/BaseGameObject.h"
#include <string>
#include <unordered_map>

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

protected:
    std::unordered_map<std::string, BaseGameObject*> gameObjects;
    std::string currentGameObjectName;
    int rectWidth;
    int rectHeight;
    int rectX;
    int rectY;
    Color rectColor;
    bool player1InGameObjects;
};

#endif //DEBUG_INFO_H
