#ifndef GBFIGHTER_CONSTANTS_H
#define GBFIGHTER_CONSTANTS_H

#include "raylib.h"
#include <functional>
#include <cmath> // for sin, cos, etc.

namespace Constants
{
const int DEFAULT_CHARACTER_SIZE = 32;

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

const Color GAMEOBJ_POS_RECT_COLOR = DARKGRAY;  // used to specify the color of the debug rectangle
const Vector2 GAMEOBJ_POS_RECT_SIZE = {3, 3}; // used to specify the size of the debug rectangle


//RayFighter Colors
const Color RAYFIGHTER_BLACK = {0, 0, 0, 255};
const Color RAYFIGHTER_DARKBROWN = {56, 24, 8, 255};
const Color RAYFIGHTER_LIGHTBROWN = {152, 88, 56, 255};
const Color RAYFIGHTER_ROSA = {208, 144, 120, 255};
const Color RAYFIGHTER_WHITE = {248, 248, 248, 255};
const Color RAYFIGHTER_LIGHTROSA = {209, 191, 184, 255};

} // namespace Constants

namespace Tween
{
// Type alias for readability
using TweenFunc = std::function<float(float)>;


// Linear interpolation
inline const TweenFunc Linear = [](float t) {
    return t;
};

// Quadratic ease in (accelerating)
inline const TweenFunc EaseInQuad = [](float t) {
    return t * t;
};

// Quadratic ease out (decelerating)
inline const TweenFunc EaseOutQuad = [](float t) {
    return t * (2 - t);
};

// Quadratic ease in/out (accel then decel)
inline const TweenFunc EaseInOutQuad = [](float t) {
    return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
};

// Cubic ease in/out
inline const TweenFunc EaseInOutCubic = [](float t) {
    return t < 0.5f ? 4 * t * t * t : (t - 1) * (2 * t - 2) * (2 * t - 2) + 1;
};

// Sine ease in/out
inline const TweenFunc EaseInOutSine = [](float t) {
    return -(cos(M_PI * t) - 1) / 2;
};

// Exponential ease out
inline const TweenFunc EaseOutExpo = [](float t) {
    return t == 1.0f ? 1.0f : 1 - pow(2, -10 * t);
};

// Bounce (ease out)
inline TweenFunc EaseOutBounce = [](float t) {
    if (t < 1 / 2.75f) {
        return 7.5625f * t * t;
    } else if (t < 2 / 2.75f) {
        t -= 1.5f / 2.75f;
        return 7.5625f * t * t + 0.75f;
    } else if (t < 2.5f / 2.75f) {
        t -= 2.25f / 2.75f;
        return 7.5625f * t * t + 0.9375f;
    } else {
        t -= 2.625f / 2.75f;
        return 7.5625f * t * t + 0.984375f;
    }
};


} // namespace Tween


namespace Global
{
// Global Variables
extern float gravity;
extern float pushReduction;

// Debug Variables
extern bool debugMode;
extern bool debugWindow;
extern bool debugGameObjBorder;
extern bool debugSpriteBorder;
extern bool debugCollisionBoxes;
extern bool debugHitboxes;
extern bool debugHurtboxes;
extern bool debugPushboxes;
extern bool debugThrowboxes;
extern bool debugThrowableboxes;
extern bool debugProximityBoxes;

} // namespace Global

namespace Colors
{
Color getRedTransparent();
}


#endif //GBFIGHTER_CONSTANTS_H
