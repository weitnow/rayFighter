#ifndef GBFIGHTER_HELPERFUNCTIONS_H
#define GBFIGHTER_HELPERFUNCTIONS_H

#include "../GameObjects/BaseGameObject.h"
#include <algorithm> // for std::abs and std::min and std::max and clamp
#include <cmath>     // For std::sqrt
#include <cstdlib>   // for std::rand and std::srand
#include <ctime>     // for std::time
#include <vector>

namespace Utils
{

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

//----------------------------------------------------------------------------------
// Template function to get a random value from any container
//----------------------------------------------------------------------------------

inline bool checkCollision(CollisionBox2D& box1, CollisionBox2D& box2)
{
    // Check collision based on their rectangles
    return CheckCollisionRecs(box1.getRectangle(),
                              box2.getRectangle()); // Assuming you are using raylib's CheckCollisionRecs()
}

inline bool checkCollision(CollisionBox2D* box1ptr, CollisionBox2D* box2ptr)
{
    // Check collision based on their rectangles
    return CheckCollisionRecs(box1ptr->getRectangle(),
                              box2ptr->getRectangle()); // Assuming you are using raylib's CheckCollisionRecs()
}

template <typename T>
T clamp(T value, T min, T max)
{
    return std::max(min, std::min(value, max));
}


class CircularCounter
{
public:
    CircularCounter(int min_value, int max_value);
    int increment();
    int decrement();
    int get_value() const;

private:
    int min_value_;
    int max_value_;
    int current_value_;
};

int calculate_circular_counter(int current_value, int increment, int min_value, int max_value);

} // namespace Utils

class Timer
{
public:
    Timer();
    void Start();                          // Start the timer
    void Stop();                           // Stop the timer
    void Reset();                          // Reset the timer
    void Restart();                        // Restart the timer
    float GetElapsedTime() const;          // Get elapsed time in seconds
    bool HasElapsed(float duration) const; // Check if a certain duration has elapsed

private:
    float startTime;
    float elapsedTime;
    bool running;
};


#endif //GBFIGHTER_HELPERFUNCTIONS_H
