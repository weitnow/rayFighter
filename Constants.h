#ifndef GBFIGHTER_CONSTANTS_H
#define GBFIGHTER_CONSTANTS_H

#include "raylib.h"

namespace Constants
{
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int BACKGROUND_WIDTH = 256;
const int PLAYER_WIDTH = 32;

const int RENDERTARGET_WIDTH = 256;
const int RENDERTARGET_HEIGHT = 144;

const int BASELINE = 102; //ground level where the player stands

const bool BACKGROUND_MUSIC = true;

const int DEFAULT_LIFE = 3;

const float INVINCIBLE_TIME = 1.0f; // time in seconds objects are invincible after taking damage

const float TIME_MULTIPLIER =
    1.f; //used to reduce the deltaTime for debugging purposes 1.0f = normal speed, 0.1f = 10x slower

const int FPS = 60;

const int PLAYER1_X = 80;
const int PLAYER2_X = 120;

// Default values used for instantiate BaseGameObjects if default constructor is used
const float Y = 102.0f;
const float X = 100.0f;
const float HEIGHT = 32.f;
const float WIDTH = 32.f;

const Color GAMEOBJ_COLOR = YELLOW;  // used to specify the color of the debug rectangle
const Vector2 GAMEOBJ_SIZE = {3, 3}; // used specify the size of the debug rectangle
} // namespace Constants

namespace Global
{
// Global Variables
extern float gravity;
extern float pushReduction;

extern bool debugMode;
extern bool debugWindow;
extern bool debugSpriteBorder;
extern bool debugCollisionBoxes;
extern bool debugHitboxes;
extern bool debugHurtboxes;
extern bool debugPushboxes;
extern bool debugThrowboxes;

} // namespace Global

namespace Colors
{
Color getRedTransparent();
}


#endif //GBFIGHTER_CONSTANTS_H
