#ifndef GBFIGHTER_CONSTANTS_H
#define GBFIGHTER_CONSTANTS_H

#include "raylib.h"

// switch DEBUG_WINDOW-Mode on and enable debug-draw and log stuff on the terminal
#define DEBUG_WINDOW // uncomment to enable debug window
#define DEBUG        // uncomment to enable debug messages and debug draw
//#define DEBUG_COLLISION_BOXES_NAMES // uncomment to enable debug messages for collision boxes names

namespace Constants
{

const int BACKGROUND_WIDTH = 258;
const int PLAYER_WIDTH = 32;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int RENDERTARGET_WIDTH = 320;
const int RENDERTARGET_HEIGHT = 180;
const int BASELINE = 142;

/*
1920 x 1080
960 x 540
640 x 360
480 x 270
320 x 180
240 x 135
*/

const bool BACKGROUND_MUSIC = false;

const int DEFAULT_LIFE = 3;

const float INVINCIBLE_TIME = 1.0f; // time in seconds objects are invincible after taking damage

const float TIME_MULTIPLIER =
    1.f; //used to reduce the deltaTime for debugging purposes 1.0f = normal speed, 0.1f = 10x slower

const int FPS = 60;

const int PLAYER1_X = 80;
const int PLAYER2_X = 120;

// Default values used for instantiate BaseGameObjects if default constructor is used
const float Y = 142.0f;
const float X = 100.0f;
const float HEIGHT = 32.f;
const float WIDTH = 32.f;


const Color GAMEOBJ_COLOR = BLUE;    // used to specify the color of the debug rectangle
const Vector2 GAMEOBJ_SIZE = {3, 3}; // used specify the size of the debug rectangle
} // namespace Constants

namespace Global
{
// Global Variables
extern float gravity;
extern float pushReduction;
} // namespace Global

namespace Colors
{
Color getRedTransparent();
}


#endif //GBFIGHTER_CONSTANTS_H
