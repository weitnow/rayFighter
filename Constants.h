#ifndef GBFIGHTER_CONSTANTS_H
#define GBFIGHTER_CONSTANTS_H

#include "raylib.h"

// switch DEBUG-Mode on and enable debug-draw and log stuff on the terminal
#define DEBUG
//#define DEBUG_CHANGE_STATE    // uncomment to enable debug messages for state changes
#define DEBUG_COLLISION_BOXES_NAMES // uncomment to enable debug messages for collision boxes names

namespace Constants
{


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int RENDERTARGET_WIDTH = 320;
const int RENDERTARGET_HEIGHT = 180;
const int BASELINE = 142;

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
} // namespace Global

namespace Colors
{
Color getRedTransparent();
}


#endif //GBFIGHTER_CONSTANTS_H
