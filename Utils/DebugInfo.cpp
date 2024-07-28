#include "DebugInfo.h"

DebugInfo::DebugInfo()
    : rectWidth(1500), rectHeight(400), rectX(10), rectY(10), rectColor(GREEN), player1InGameObjects(false)
{
}

DebugInfo::~DebugInfo()
{
}

void DebugInfo::addGameObject(const std::string& name, BaseGameObject* gameObject)
{
    if (gameObjects.empty())
    {
        currentGameObjectName = name;
    }
    gameObjects[name] = gameObject;
    if (name == "Player1")
    {
        player1InGameObjects = true;
    }
}

void DebugInfo::removeGameObject(std::string& name)
{
    gameObjects.erase(name);
    if (currentGameObjectName == name)
    {
        if (!gameObjects.empty())
        {
            currentGameObjectName = gameObjects.begin()->first;
        }
        std::cout << "currentGameObjectName: " << currentGameObjectName << std::endl;
    }
}

bool DebugInfo::showNextGameObject()
{
    if (gameObjects.empty())
    {
        return false;
    }
    else if (gameObjects.size() == 1)
    {
        return false;
    }
    else
    {
        // go to next game object
        auto it = gameObjects.find(currentGameObjectName);
        if (it != gameObjects.end())
        {
            it++;
            if (it == gameObjects.end())
            {
                it = gameObjects.begin();
            }
            currentGameObjectName = it->first;
        }
        return true;
    }
}

void DebugInfo::update(float deltaTime)
{
}

void DebugInfo::draw()
{
    // Draw rectangle and FPS
    DrawRectangle(rectX, rectY, rectWidth, rectHeight, rectColor);
    DrawFPS(rectX + 10, rectY + 10);

    // Draw Player1. Is there is not "Player1" in gameObjects draw a message, that player1 is not found
    if (player1InGameObjects)
    {
        std::string name_pl1 = "GameObjName: Player1";
        std::string position_pl1 = "Pos: " + std::to_string(static_cast<int>(gameObjects["Player1"]->getPos().x)) +
                                   ", " + std::to_string(static_cast<int>(gameObjects["Player1"]->getPos().y));

        DrawText(name_pl1.c_str(), rectX + 10, rectY + 50, 20, BLACK);
        DrawText(position_pl1.c_str(), rectX + 10, rectY + 70, 20, BLACK);
    }
    else
    {

        DrawText("No Obj named \"Player1\" found", rectX + 800, rectY + 50, 20, BLACK);
    }

    // Draw other game objects
    std::string name = "GameObjName: " + currentGameObjectName;
    std::string position = "Pos: " + std::to_string(static_cast<int>(gameObjects[currentGameObjectName]->getPos().x)) +
                           ", " + std::to_string(static_cast<int>(gameObjects[currentGameObjectName]->getPos().y));

    DrawText(name.c_str(), rectX + 700, rectY + 50, 20, BLACK);
    DrawText(position.c_str(), rectX + 700, rectY + 70, 20, BLACK);
}
