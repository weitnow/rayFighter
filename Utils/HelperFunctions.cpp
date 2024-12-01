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

/* #endregion */
