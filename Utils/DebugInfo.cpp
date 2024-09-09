#include "DebugInfo.h"

constexpr int RECT_WIDTH = 1520;
constexpr int RECT_HEIGHT = 400;
constexpr int RECT_X = 10;
constexpr int RECT_Y = 10;
constexpr Color RECT_COLOR = GREEN;
constexpr int TEXT_SIZE = 20;
constexpr Color TEXT_COLOR = BLACK;

DebugInfo::DebugInfo()
    : rectWidth(RECT_WIDTH), rectHeight(RECT_HEIGHT), rectX(RECT_X), rectY(RECT_Y), rectColor(RECT_COLOR),
      player1InGameObjects(false)
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

    if (currentGameObjectName == name && !gameObjects.empty())
    {
        currentGameObjectName = gameObjects.begin()->first;
    }

    std::cout << "currentGameObjectName: " << currentGameObjectName << std::endl;
}

bool DebugInfo::showNextGameObject()
{
    if (gameObjects.size() <= 1)
    {
        return false; // No switching possible if we have 0 or 1 object
    }

    // Move to the next game object in the map
    auto it = gameObjects.find(currentGameObjectName);
    if (it != gameObjects.end())
    {
        ++it;
        if (it == gameObjects.end())
        {
            it = gameObjects.begin(); // Wrap around to the beginning
        }
        currentGameObjectName = it->first;
        return true;
    }

    return false;
}

void DebugInfo::update(float deltaTime)
{
    // Placeholder for future updates
}

// Function to draw data for any game object
void DebugInfo::drawGameObjectData(BaseGameObject* gameObject, const std::string& objectName, int x, int y)
{
    BaseCharacter* character = static_cast<BaseCharacter*>(gameObject);

    DrawText(("DebugName: " + objectName).c_str(), x, y, TEXT_SIZE, TEXT_COLOR);
    DrawText(("Pos: " + std::to_string(static_cast<int>(gameObject->getPos().x)) + ", " +
              std::to_string(static_cast<int>(gameObject->getPos().y)))
                 .c_str(),
             x,
             y + 20,
             TEXT_SIZE,
             TEXT_COLOR);
    DrawText(("FrameTag: " + gameObject->getCurrentFrameTag()).c_str(), x, y + 40, TEXT_SIZE, TEXT_COLOR);
    DrawText(("CurrentState: " + character->getCurrentState()).c_str(), x, y + 60, TEXT_SIZE, TEXT_COLOR);
    DrawText(("IsOnGround: " + std::to_string(character->getIsOnGround())).c_str(), x, y + 80, TEXT_SIZE, TEXT_COLOR);

    int moveDirectionX = static_cast<int>(character->getMoveDirection().x);
    int moveDirectionY = static_cast<int>(character->getMoveDirection().y);
    DrawText(("MoveDirection: " + std::to_string(moveDirectionX) + ", " + std::to_string(moveDirectionY)).c_str(),
             x,
             y + 100,
             TEXT_SIZE,
             TEXT_COLOR);

    int milliseconds = static_cast<int>(gameObject->getAnim()->getDurationCurrentFrame() * 1000);
    DrawText(("Frameduration: " + std::to_string(milliseconds)).c_str(), x, y + 120, TEXT_SIZE, TEXT_COLOR);
    DrawText(("isLeft: " + std::to_string(character->getIsLeft())).c_str(), x, y + 140, TEXT_SIZE, TEXT_COLOR);
    DrawText(("PlayerNumber: " + std::to_string(character->getPlayerNumber())).c_str(),
             x,
             y + 160,
             TEXT_SIZE,
             TEXT_COLOR);
    DrawText(("ObjName: " + gameObject->getObjName()).c_str(), x, y + 180, TEXT_SIZE, TEXT_COLOR);
}

void DebugInfo::draw()
{
    // Draw rectangle and FPS
    DrawRectangle(rectX, rectY, rectWidth, rectHeight, rectColor);
    DrawFPS(rectX + 10, rectY + 10);

    // Draw Player1 data if available
    if (player1InGameObjects && gameObjects.find("Player1") != gameObjects.end())
    {
        drawGameObjectData(gameObjects["Player1"], "Player1", rectX + 10, rectY + 50);
    }
    else
    {
        DrawText("No Obj named \"Player1\" found", rectX + 800, rectY + 50, TEXT_SIZE, TEXT_COLOR);
    }

    // Draw other game objects
    if (gameObjects.find(currentGameObjectName) != gameObjects.end())
    {
        drawGameObjectData(gameObjects[currentGameObjectName], currentGameObjectName, rectX + 700, rectY + 50);
    }
}
