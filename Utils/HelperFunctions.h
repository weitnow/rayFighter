#ifndef GBFIGHTER_HELPERFUNCTIONS_H
#define GBFIGHTER_HELPERFUNCTIONS_H

#include "../GameObjects/BaseGameObject.h"
#include <cmath> // For std::sqrt

inline float calculateDistance(const BaseGameObject& obj1, const BaseGameObject& obj2)
{
    float dx = obj1.getPos().x - obj2.getPos().x;
    float dy = obj1.getPos().y - obj2.getPos().y;
    return std::sqrt(dx * dx + dy * dy);
}
inline float calculateDistanceX(const BaseGameObject& obj1, const BaseGameObject& obj2)
{
    return std::abs(obj1.getPos().x - obj2.getPos().x);
}

inline float calculateDistanceY(const BaseGameObject& obj1, const BaseGameObject& obj2)
{
    return std::abs(obj1.getPos().y - obj2.getPos().y);
}

#endif //GBFIGHTER_HELPERFUNCTIONS_H
