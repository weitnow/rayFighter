#include "HelperFunctions.h"

/* #region ---Timer class--- */

Timer::Timer() : startTime(0.0f), elapsedTime(0.0f), running(false)
{
}

void Timer::Start()
{
    if (!running)
    {
        startTime = GetTime();
        running = true;
    }
}

void Timer::Stop()
{
    if (running)
    {
        elapsedTime += GetTime() - startTime;
        running = false;
    }
}

void Timer::Reset()
{
    startTime = 0.0f;
    elapsedTime = 0.0f;
    running = false;
}

void Timer::Restart()
{
    Reset();
    Start();
}

float Timer::GetElapsedTime() const
{
    if (running)
    {
        return elapsedTime + (GetTime() - startTime);
    }
    return elapsedTime;
}

bool Timer::HasElapsed(float duration) const
{
    return GetElapsedTime() >= duration;
}


/* #region ---CircularCounter class--- */
Utils::CircularCounter::CircularCounter(int min_value, int max_value)
    : min_value_{min_value}, max_value_{max_value}, current_value_{min_value}
{
}

int Utils::CircularCounter::increment()
{
    current_value_ = (current_value_ + 1) % (max_value_ - min_value_ + 1) + min_value_;
    return current_value_;
}

int Utils::CircularCounter::decrement()
{
    current_value_ = (current_value_ - 1 + max_value_ - min_value_ + 1) % (max_value_ - min_value_ + 1) + min_value_;
    return current_value_;
}

int Utils::CircularCounter::get_value() const
{
    return current_value_;
}

bool Utils::CircularCounter::set_value(int value)
{
    if (value < min_value_ || value > max_value_)
    {
        std::cout << "Error Utils::CircularCounter::set_value, value is outside min or max values" << std::endl;
        return false;
    }
    else
    {
        current_value_ = value;
        return true;
    }
}

/* #endregion */
