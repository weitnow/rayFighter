#ifndef GBFIGHTER_CONSTANTS_H
#define GBFIGHTER_CONSTANTS_H

#include "raylib.h"

namespace Constants
{
const int PLAYER_PIXELSIZE = 32;

const int RENDERTARGET_WIDTH = 256;
const int RENDERTARGET_HEIGHT = 144;

const int STAGE_WIDTH = 416 - 64; // = Stage is 416 pixel wide, but the camera is 64 pixel to the left,
                                  // 416 - 64 = 352 where 32 pixel are the player
const int STAGE_OFFSET = -64;

const int BASELINE = 102; //ground level where the player stands

const bool BACKGROUND_MUSIC = false;

const int DEFAULT_LIFE = 3;

const float INVINCIBLE_TIME = 1.0f; // time in seconds objects are invincible after taking damage

const int FPS = 60;

const int PLAYER1_X = 64 + 16;
const int PLAYER2_X = 192 - 16;

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
