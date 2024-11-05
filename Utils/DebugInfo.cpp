#include "DebugInfo.h"
#include "HelperFunctions.h"
#include "Screen2DManager.h"

constexpr int RECT_WIDTH = 1520;
constexpr int RECT_HEIGHT = 400;
constexpr int RECT_X = 10;
constexpr int RECT_Y = 10;
constexpr Color RECT_COLOR = GREEN;
constexpr int TEXT_SIZE = 20;
constexpr Color TEXT_COLOR = BLACK;

DebugInfo::DebugInfo(BaseState* baseState)
    : rectWidth(RECT_WIDTH), rectHeight(RECT_HEIGHT), rectX(RECT_X), rectY(RECT_Y), rectColor(RECT_COLOR),
      player1InGameObjects(false), baseState{baseState}, player1{baseState->player1}, player2{baseState->player2}
{
}

DebugInfo::~DebugInfo()
{
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

void DebugInfo::setDebugMode(bool debugMode)
{
    if ((!player1) || (!player2)) // if either of them is nullptr try to load them from the baseState
    {
        player1 = baseState->player1;
        player2 = baseState->player2;

        if ((!player1) || (!player2))
        {
            throw std::runtime_error(
                "DebugInfo.cpp -> player1 and/or player2 is nullptr"); //if there are still nullptr, because the gamestate has no players throw a runtimeerror
        }
    }

    Global::debugMode = debugMode;
    Global::debugWindow = debugMode;
    Global::debugSpriteBorder = false; //debugMode;
    Global::debugCollisionBoxes = debugMode;
    Global::debugHitboxes = debugMode;
    Global::debugHurtboxes = debugMode;
    Global::debugPushboxes = false;  //debugMode;
    Global::debugThrowboxes = false; //debugMode;

    if (debugMode)
    {

        std::cout << "DebugMode is set to true" << std::endl;

        // change resolution of the renderTarget
        baseState->screen2DManager->setResolution(Resolution::R_1120x630);
    }
    else
    {
        std::cout << "DebugMode is set to false" << std::endl;
        // change resolution of the renderTarget
        baseState->screen2DManager->setResolution(Resolution::R_1920x1080);
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
    DrawText(("hasAnimJustFinishedPlusLastFrameDuration: " +
              std::to_string(character->getAnim()->hasAnimJustFinishedPlusLastFrameDuration()))
                 .c_str(),
             x,
             y + 260,
             TEXT_SIZE,
             TEXT_COLOR);
    DrawText(("isAlive: " + std::to_string(character->getIsAlive())).c_str(), x, y + 280, TEXT_SIZE, TEXT_COLOR);
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

    drawGameObjectData(player1, "Player1", rectX + 10, rectY + 50);


    /* #endregion*/

    /* #region DRAW RIGHT DEBUG_WINDOW WINDOW*/
    int windowX = 1545;
    int windowY = 0;
    int windowWidth = 374;
    int windowHeight = 1070;


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
    float distanceBetweenPlayers = Utils::calculateDistance(*player1, *player2);

    // Use ostringstream to format the distance
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << distanceBetweenPlayers; // Set precision to 2 decimal places
    std::string distanceText = "Distance betw Players: " + oss.str();

    DrawText(distanceText.c_str(), windowX + 10, windowY + 70, TEXT_SIZE, TEXT_COLOR);

    DrawText(("P1 is flipped: " + std::to_string(player1->getIsFlippedX())).c_str(),
             windowX + 10,
             windowY + 90,
             TEXT_SIZE,
             TEXT_COLOR);

    DrawText(("P2 is flipped: " + std::to_string(player2->getIsFlippedX())).c_str(),
             windowX + 10,
             windowY + 110,
             TEXT_SIZE,
             TEXT_COLOR);


    /* #endregion*/
}
