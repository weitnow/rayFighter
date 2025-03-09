#ifndef GBFIGHTER_CONSTANTS_H
#define GBFIGHTER_CONSTANTS_H

#include "raylib.h"

namespace Constants
{
const int PLAYER_PIXELSIZE = 32;

const int RENDERTARGET_WIDTH = 256;
const int RENDERTARGET_HEIGHT = 144;

const int CAM_MOST_LEFT = 0;    // if the camera has value 0 it means the camera is at the most left of the stage
const int CAM_MIDDLE = 80;      // if the camera has value 80 it means the camera is in the middle of the stage
const int CAM_MOST_RIGHT = 160; // if the camera has value 160 it means the camera is at the most right of the stage
const int STAGE_WIDTH = 416;

const int BASELINE = 102; //ground level where the player stands

const float INVINCIBLE_TIME = 1.0f; // time in seconds objects are invincible after taking damage

const int FPS = 60;

// 208 = middle of the screen, but x/y of the Fighters is taken in the upperleft Corner of the 32x32 Sprite
const int PLAYER1_X = 128; //128;
const int PLAYER2_X = 256; //256;

const Color GAMEOBJ_COLOR = YELLOW;  // used to specify the color of the debug rectangle
const Vector2 GAMEOBJ_SIZE = {3, 3}; // used specify the size of the debug rectangle


//RayFighter Colors
const Color RAYFIGHTER_BLACK = {0, 0, 0, 255};
const Color RAYFIGHTER_DARKBROWN = {56, 24, 8, 255};
const Color RAYFIGHTER_LIGHTBROWN = {152, 88, 56, 255};
const Color RAYFIGHTER_ROSA = {208, 144, 120, 255};
const Color RAYFIGHTER_WHITE = {248, 248, 248, 255};
const Color RAYFIGHTER_LIGHTROSA = {209, 191, 184, 255};


} // namespace Constants

namespace Global
{
// Global Variables
extern float gravity;
extern float pushReduction;

// Debug Variables
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
