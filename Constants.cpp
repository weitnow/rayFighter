#include "Constants.h"

Color Colors::getRedTransparent()
{
    Color redTransparent = RED;
    redTransparent.a = 90;
    return redTransparent;
}

float Global::gravity = 830.f;
float Global::pushReduction = 1000.f;

bool Global::debugMode = false;           // will be set by GameManager->setDebugMode
bool Global::debugWindow = false;         // will be set by GameManager->setDebugMode
bool Global::debugSpriteBorder = false;   // will be set by GameManager->setDebugModegame->debugInfo->draw();
bool Global::debugCollisionBoxes = false; // will be set by GameManager->setDebugMode
bool Global::debugHitboxes = false;       // will be set by GameManager->setDebugMode
bool Global::debugHurtboxes = false;      // will be set by GameManager->setDebugMode
bool Global::debugPushboxes = false;      // will be set by GameManager->setDebugMode
bool Global::debugThrowboxes = false;     // will be set by GameManager->setDebugMode
bool Global::debugProximityBoxes = false; // will be set by GameManager->setDebugMode
