#include "DebugInfo.h"
#include "HelperFunctions.h"

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
    BaseCharacter* character = dynamic_cast<BaseCharacter*>(gameObject);

    if (character != nullptr) // if the cast was successful, we have a character
    {
        _drawCharacterData(character, objectName, x, y);
    }
    else // otherwise character is a nullptr and we have to use gameObject
    {
        _drawGameObjectData(gameObject, objectName, x, y);
    }
}

void DebugInfo::_drawCharacterData(BaseCharacter* character, const std::string& objectName, int x, int y)
{
    DrawText(("DebugName: " + objectName).c_str(), x, y, TEXT_SIZE, TEXT_COLOR);
    DrawText(("Pos: " + std::to_string(static_cast<int>(character->getPos().x)) + ", " +
              std::to_string(static_cast<int>(character->getPos().y)))
                 .c_str(),
             x,
             y + 20,
             TEXT_SIZE,
             TEXT_COLOR);
    DrawText(("FrameTag: " + character->getCurrentFrameTag()).c_str(), x, y + 40, TEXT_SIZE, TEXT_COLOR);
    DrawText(("CurrentState: " + character->getCurrentState()).c_str(), x, y + 60, TEXT_SIZE, TEXT_COLOR);
    DrawText(("IsOnGround: " + std::to_string(character->getIsOnGround())).c_str(), x, y + 80, TEXT_SIZE, TEXT_COLOR);

    int moveDirectionX = character->getMoveVector().x;
    int moveDirectionY = character->getMoveVector().y;
    DrawText(("MoveDirection: " + std::to_string(moveDirectionX) + ", " + std::to_string(moveDirectionY)).c_str(),
             x,
             y + 100,
             TEXT_SIZE,
             TEXT_COLOR);

    float pushVectorX = character->getPushVector().x;
    float pushVectorY = character->getPushVector().y;
    DrawText(("PushVector: " + std::to_string(pushVectorX) + ", " + std::to_string(pushVectorY)).c_str(),
             x,
             y + 120,
             TEXT_SIZE,
             TEXT_COLOR);

    int milliseconds = character->getAnim()->getDurationCurrentFrame() * 1000;
    DrawText(("Frameduration: " + std::to_string(milliseconds)).c_str(), x, y + 140, TEXT_SIZE, TEXT_COLOR);
    DrawText(("isLeft: " + std::to_string(character->getIsLeft())).c_str(), x, y + 160, TEXT_SIZE, TEXT_COLOR);
    DrawText(("PlayerNumber: " + std::to_string(character->getPlayerNumber())).c_str(),
             x,
             y + 180,
             TEXT_SIZE,
             TEXT_COLOR);
    DrawText(("ObjName: " + character->getObjName()).c_str(), x, y + 200, TEXT_SIZE, TEXT_COLOR);
    DrawText(("currentFrame: " + std::to_string(character->getAnim()->getCurrentFrame())).c_str(),
             x,
             y + 220,
             TEXT_SIZE,
             TEXT_COLOR);
    DrawText(("hasAnimJustFinished: " + std::to_string(character->getAnim()->hasAnimJustFinished())).c_str(),
             x,
             y + 240,
             TEXT_SIZE,
             TEXT_COLOR);
}

void DebugInfo::_drawGameObjectData(BaseGameObject* gameObject, const std::string& objectName, int x, int y)
{
    DrawText(("DebugName: " + objectName).c_str(), x, y, TEXT_SIZE, TEXT_COLOR);
    DrawText(("Pos: " + std::to_string(static_cast<int>(gameObject->getPos().x)) + ", " +
              std::to_string(static_cast<int>(gameObject->getPos().y)))
                 .c_str(),
             x,
             y + 20,
             TEXT_SIZE,
             TEXT_COLOR);
    DrawText(("PushVector: " + std::to_string(gameObject->getPushVector().x) + ", " +
              std::to_string(gameObject->getPushVector().y))
                 .c_str(),
             x,
             y + 40,
             TEXT_SIZE,
             TEXT_COLOR);
    DrawText(("FrameTag: " + gameObject->getCurrentFrameTag()).c_str(), x, y + 60, TEXT_SIZE, TEXT_COLOR);
    DrawText(("ObjName: " + gameObject->getObjName()).c_str(), x, y + 80, TEXT_SIZE, TEXT_COLOR);
    DrawText(("currentFrame: " + std::to_string(gameObject->getAnim()->getCurrentFrame())).c_str(),
             x,
             y + 100,
             TEXT_SIZE,
             TEXT_COLOR);
    DrawText(("hasAnimJustFinished: " + std::to_string(gameObject->getAnim()->hasAnimJustFinished())).c_str(),
             x,
             y + 120,
             TEXT_SIZE,
             TEXT_COLOR);
}

void DebugInfo::draw()
{
    /* #region DRAW UPPER DEBUG_WINDOW WINDOW*/
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
    /* #endregion*/

    /* #region DRAW RIGHT DEBUG_WINDOW WINDOW*/
    int windowX = 1545;
    int windowY = 0;
    int windowWidth = 374;
    int windowHeight = 1070;

    // get reference to statemachine of player1
    GameManager& gameManager = GameManager::getInstance();
    BaseCharacter* player1 = gameManager.getBaseCharacter("player1");
    BaseCharacter* player2 = gameManager.getBaseCharacter("player2");
    if (player1 != nullptr && player2 != nullptr)
    {
        Statemachine& statemachine = player1->getStatemachine();
        DrawText("Statemachine of Player 1", windowX + 10, windowY + 10, TEXT_SIZE, TEXT_COLOR);
        DrawText(("Current State: " + statemachine.getCurrentStateAsString()).c_str(),
                 windowX + 10,
                 windowY + 30,
                 TEXT_SIZE,
                 TEXT_COLOR);
        DrawText(("Previous State: " + statemachine.getPreviousStateAsString()).c_str(),
                 windowX + 10,
                 windowY + 50,
                 TEXT_SIZE,
                 TEXT_COLOR);

        // Calculate distance
        float distanceBetweenPlayers = calculateDistance(*player1, *player2);

        // Use ostringstream to format the distance
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << distanceBetweenPlayers; // Set precision to 2 decimal places
        std::string distanceText = "Distance betw Players: " + oss.str();

        DrawText(distanceText.c_str(), windowX + 10, windowY + 70, TEXT_SIZE, TEXT_COLOR);
    }


    /* #endregion*/
}
