#include "Powerbar.h"
#include "../Constants.h"

Powerbar::Powerbar(Vector2 pos,
                   int height,
                   int width,
                   int maxValue,
                   Color color,
                   int playerNumber,
                   bool drawReversed,
                   std::string name)
    : position(pos), height(height), width(width), currentValue(maxValue), maxValue(maxValue), barColor(color),
      fighterName(name), playerNumber(playerNumber), drawReversed(drawReversed)
{
    _calculateNamePosX();
}

Powerbar::~Powerbar()
{
}

void Powerbar::Draw()
{
    // Calculate the width of the health bar based on the current health
    float healthPercentage = static_cast<float>(currentValue) / static_cast<float>(maxValue);
    float currentBarWidth = width * healthPercentage;

    if (playerNumber == 1)
    {


        if (drawReversed)
        {
            // Draw the actual health bar
            DrawRectangle(position.x, position.y, static_cast<int>(currentBarWidth), height, barColor);
        }
        else
        {
            // Calculate the x position for the shrinking effect from the outside
            float currentBarPositionX = position.x + (width - currentBarWidth);
            // Draw the actual health bar from the outside to the inside
            DrawRectangle(static_cast<int>(currentBarPositionX),
                          position.y,
                          static_cast<int>(currentBarWidth),
                          height,
                          barColor);
        }
    }
    else if (playerNumber == 2)


        if (drawReversed)
        {
            // Calculate the x position for the shrinking effect from the outside
            float currentBarPositionX = position.x + (width - currentBarWidth);
            // Draw the actual health bar from the outside to the inside
            DrawRectangle(static_cast<int>(currentBarPositionX),
                          position.y,
                          static_cast<int>(currentBarWidth),
                          height,
                          barColor);
        }
        else
        {
            // Draw the actual health bar
            DrawRectangle(position.x, position.y, static_cast<int>(currentBarWidth), height, barColor);
        }

    // check if name is empty
    if (fighterName.empty())
    {
        return;
    }
    // otherwise draw the fighter's name above the health bar
    DrawText(fighterName.c_str(), namePosX, position.y - 12, 8, Constants::RAYFIGHTER_LIGHTROSA);
}

void Powerbar::ChangeValue(int newHealth)
{
    currentValue = newHealth;
    if (currentValue < 0)
        currentValue = 0; // Prevent negative health
}


void Powerbar::_calculateNamePosX()
{
    // Calculate the namePosX for the fighter's name
    if (playerNumber == 1)
    {
        namePosX = position.x + 5;
    }
    else if (playerNumber == 2)
    {
        namePosX = position.x + width - MeasureText(fighterName.c_str(), 8) - 5;
    }
}
