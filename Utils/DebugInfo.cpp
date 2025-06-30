#include "DebugInfo.h"
#include "HelperFunctions.h"
#include "Screen2DManager.h"

constexpr int RECT_WIDTH = 1520;
constexpr int RECT_HEIGHT = 400;
constexpr int RECT_X = 10;
constexpr int RECT_Y = 10;
constexpr int TEXT_SIZE = 20;
constexpr Color TEXT_COLOR = GREEN;
constexpr int LINE_SPACING = 20;

DebugInfo::DebugInfo(BaseState* baseState)
    : rectWidth(RECT_WIDTH), rectHeight(RECT_HEIGHT), rectX(RECT_X), rectY(RECT_Y), player1InGameObjects(false),
      baseState{baseState}, gameState{nullptr}, player1{baseState->player1}, player2{baseState->player2},
      statemachine{nullptr}
{
    // try to cast the baseState to a gameState
    gameState = dynamic_cast<GameState*>(baseState);
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
        _drawCharacterDataInternal(character, objectName, x, y);
    }
    else // otherwise character is a nullptr and we have to use gameObject
    {
        _drawGameObjectDataInternal(gameObject, objectName, x, y);
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
    Global::debugSpriteBorder = debugMode;
    Global::debugCollisionBoxes = debugMode;
    Global::debugHitboxes = debugMode;
    Global::debugHurtboxes = debugMode;
    Global::debugPushboxes = false;  // false or debugMode;
    Global::debugThrowboxes = debugMode;
    Global::debugThrowableboxes = debugMode;
    Global::debugProximityBoxes = debugMode;

    if (debugMode)
    {

        std::cout << "DebugMode is set to true" << std::endl;

        // change screenResolution to fullHD
        baseState->screen2DManager->changeScreenResolution(ScreenResolution::S_1920x1080);

        // change resolution of the renderTarget
        baseState->screen2DManager->_setRenderResolution(RenderResolution::R_1120x630);
    }
    else
    {
        std::cout << "DebugMode is set to false" << std::endl;

        // load the saved screenResolution
        baseState->screen2DManager->loadScreenResolution();
    }
}

void DebugInfo::_drawCharacterDataInternal(BaseCharacter* character, const std::string& objectName, int x, int y)
{
    _drawDebugText("DebugName", objectName, x, y);

    y += LINE_SPACING;
    _drawDebugText("Pos",
                   std::to_string(static_cast<int>(character->getPos().x)) + ", " +
                       std::to_string(static_cast<int>(character->getPos().y)),
                   x,
                   y);

    y += LINE_SPACING;
    _drawDebugText("ScreenPos", std::to_string(gameState->_getScreenPosXofObject(*character)), x, y);

    y += LINE_SPACING;
    _drawDebugText("FrameTag", character->getCurrentFrameTag(), x, y);

    y += LINE_SPACING;
    _drawDebugText("CurrentState", character->getCurrentState(), x, y);

    y += LINE_SPACING;
    _drawDebugText("IsOnGround", std::to_string(character->getIsOnGround()), x, y);

    y += LINE_SPACING;
    _drawDebugText("MoveDirection",
                   std::to_string(character->getMoveVector().x) + ", " + std::to_string(character->getMoveVector().y),
                   x,
                   y);

    y += LINE_SPACING;
    _drawDebugText("PushVector",
                   std::to_string(character->getPushVector().x) + ", " + std::to_string(character->getPushVector().y),
                   x,
                   y);

    y += LINE_SPACING;
    _drawDebugText("Frameduration", std::to_string(character->getAnimFile()->getDurationCurrentFrame() * 1000), x, y);

    y += LINE_SPACING;
    _drawDebugText("isLeft", std::to_string(character->getIsLeft()), x, y);

    y += LINE_SPACING;
    _drawDebugText("PlayerNumber", std::to_string(character->getPlayerNumber()), x, y);

    y += LINE_SPACING;
    _drawDebugText("ObjName", character->getObjName(), x, y);

    y += LINE_SPACING;
    _drawDebugText("currentFrame", std::to_string(character->getAnimFile()->getCurrentFrame()), x, y);

    y += LINE_SPACING;
    _drawDebugText("hasAnimFinished", std::to_string(character->getAnimFile()->hasAnimFinished()), x, y);

    y += LINE_SPACING;
    _drawDebugText("hasAnimFinishedPlusLastFrameDuration",
                   std::to_string(character->getAnimFile()->hasAnimFinishedPlusLastFrameDuration()),
                   x,
                   y);

    y += LINE_SPACING;
    _drawDebugText("isAlive", std::to_string(character->getIsAlive()), x, y);
}

void DebugInfo::_drawGameObjectDataInternal(BaseGameObject* gameObject, const std::string& objectName, int x, int y)
{
    _drawDebugText("DebugName", objectName, x, y);

    y += LINE_SPACING;
    _drawDebugText("Pos",
                   std::to_string(static_cast<int>(gameObject->getPos().x)) + ", " +
                       std::to_string(static_cast<int>(gameObject->getPos().y)),
                   x,
                   y);

    y += LINE_SPACING;
    _drawDebugText("PushVector",
                   std::to_string(gameObject->getPushVector().x) + ", " + std::to_string(gameObject->getPushVector().y),
                   x,
                   y);

    y += LINE_SPACING;
    _drawDebugText("FrameTag", gameObject->getCurrentFrameTag(), x, y);

    y += LINE_SPACING;
    _drawDebugText("ObjName", gameObject->getObjName(), x, y);

    y += LINE_SPACING;
    _drawDebugText("currentFrame", std::to_string(gameObject->getAnimFile()->getCurrentFrame()), x, y);

    y += LINE_SPACING;
    _drawDebugText("hasAnimFinished", std::to_string(gameObject->getAnimFile()->hasAnimFinished()), x, y);
}

void DebugInfo::_drawDebugText(const std::string& label, const std::string& value, int x, int y)
{
    DrawText((label + ": " + value).c_str(), x, y, TEXT_SIZE, TEXT_COLOR);
}

void DebugInfo::draw()
{
    /* #region DRAW UPPER DEBUG_WINDOW WINDOW*/

    // FPS
    DrawFPS(rectX + 10, rectY + 10);

    // Draw Player1 data if available
    drawGameObjectData(player1, "Player1", rectX + 10, rectY + 50);

    // Draw Player2 data if available
    drawGameObjectData(player2, "Player2", rectX + 600, rectY + 50);

    /* #endregion*/

    /* #region DRAW RIGHT DEBUG_WINDOW WINDOW*/
    int windowX = 1545;
    int windowY = 0;
    int windowWidth = 374;
    int windowHeight = 1070;
    constexpr int startOffset = 10; // Inital offset for the text placement
    int y = windowY + startOffset;

    // check if statemachine is nullptr and if so, try to load it
    if (statemachine == nullptr)
    {
        statemachine = &player1->getStatemachine();
    }


    // draw title "Statemachine of Player 1"
    DrawText("Statemachine of Player 1", windowX + startOffset, y, TEXT_SIZE, TEXT_COLOR);

    y += LINE_SPACING;
    _drawDebugText("Current State", statemachine->getCurrentStateAsString(), windowX + startOffset, y);

    y += LINE_SPACING;
    _drawDebugText("Previous State", statemachine->getPreviousStateAsString(), windowX + startOffset, y);

    // Calculate distance
    float distanceBetweenPlayers = Utils::calculateDistance(*player1, *player2);

    y += LINE_SPACING;
    _drawDebugText("Distance btw. Players", std::to_string(distanceBetweenPlayers), windowX + startOffset, y);

    y += LINE_SPACING;
    _drawDebugText("P1 is flipped", std::to_string(player1->getIsFlippedX()), windowX + startOffset, y);

    y += LINE_SPACING;
    _drawDebugText("P2 is flipped", std::to_string(player2->getIsFlippedX()), windowX + startOffset, y);

    Vector2 middlePoint = gameState->getMiddlePointBetweenPlayers();
    y += LINE_SPACING;
    _drawDebugText("MiddlePoint",
                   std::to_string(middlePoint.x) + ", " + std::to_string(middlePoint.y),
                   windowX + startOffset,
                   y);

    y += LINE_SPACING;
    _drawDebugText("Camera X/Y",
                   std::to_string(gameState->cameraX) + "/" + std::to_string(gameState->cameraY),
                   windowX + startOffset,
                   y);

    /* #endregion*/
}
