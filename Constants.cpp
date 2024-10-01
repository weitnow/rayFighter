#include "Constants.h"

Color Colors::getRedTransparent()
{
    Color redTransparent = RED;
    redTransparent.a = 90;
    return redTransparent;
}

float Global::gravity = 830.f;
float Global::pushReduction = 1000.f;
