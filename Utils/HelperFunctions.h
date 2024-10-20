#ifndef GBFIGHTER_HELPERFUNCTIONS_H
#define GBFIGHTER_HELPERFUNCTIONS_H

#include "../GameObjects/BaseGameObject.h"
#include <cmath>   // For std::sqrt
#include <cstdlib> // for std::rand and std::srand
#include <ctime>   // for std::time
#include <vector>

//----------------------------------------------------------------------------------
// Calculate Distance between two GameObjects
//----------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------
// Template function to get a random value from any container
//----------------------------------------------------------------------------------
template <typename T>
T getRandomValueOf(const std::vector<T>& container)
{
    // Seed the random number generator (once in your main function)
    if (container.empty())
    {
        throw std::invalid_argument("Container is empty");
    }

    // Generate a random index between 0 and container.size() - 1
    int randomIndex = std::rand() % container.size();

    // Return the random value
    return container[randomIndex];
}

// Call this function somewhere in main or once in a global scope to seed the random generator
inline void initializeRandom()
{
    std::srand(static_cast<unsigned>(std::time(0)));
}


#endif //GBFIGHTER_HELPERFUNCTIONS_H
