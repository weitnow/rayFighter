//
// Created by weitnow on 12/25/23.
//

#ifndef GBFIGHTER_CONSTANTS_H
#define GBFIGHTER_CONSTANTS_H

#include "raylib.h"

// switch DEBUG-Mode on and enable debug-draw and log stuff on the terminal
#define DEBUG

namespace Constants {
    // Default values used for instantiate BaseGameObjects if default constructor is used
    const float Y = 300.0f;
    const float X = 100.0f;
    const float HEIGHT = 32.f;
    const float WIDTH = 32.f;
}

namespace Colors {
    Color getRedTransparent();
}

#endif //GBFIGHTER_CONSTANTS_H
