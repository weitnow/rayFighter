#include "Constants.h"

Color Colors::getRedTransparent()
{
    Color redTransparent = RED;
    redTransparent.a = 90;
    return redTransparent;
}

float Global::gravity = 13.f;
