#include "Lifebar.h"

Lifebar::Lifebar(Vector2 pos,
                 int height,
                 int width,
                 int maxHp,
                 Color color,
                 Color border,
                 std::string name,
                 int playerNumber)
    : position(pos), height(height), width(width), currentHealth(maxHp), maxHealth(maxHp), barColor(color),
      borderColor(border), fighterName(name), playerNumber(playerNumber)
{
}

Lifebar::~Lifebar()
{
}

void Lifebar::Draw()
{
    // Calculate the width of the health bar based on the current health
    float healthPercentage = static_cast<float>(currentHealth) / static_cast<float>(maxHealth);
    float currentBarWidth = width * healthPercentage;

    // Pos X for drawing the name of the fighter
    float namePosX;

    if (playerNumber == 1)
    {
        // Calculate the x position for the shrinking effect from the outside
        float currentBarPositionX = position.x + (width - currentBarWidth);

        // Draw the actual health bar from the outside to the inside
        DrawRectangle(static_cast<int>(currentBarPositionX),
                      position.y,
                      static_cast<int>(currentBarWidth),
                      height,
                      barColor);

        // Calculate the namePosX for the fighter's name
        namePosX = position.x + 5;
    }
    else if (playerNumber == 2)
    {
        // Draw the actual health bar
        DrawRectangle(position.x, position.y, static_cast<int>(currentBarWidth), height, barColor);

        // Calculate the namePosX for the fighter's name
        //namePosX = position.x - MeasureText(fighterName.c_str(), 8) - 5;
        namePosX = position.x + width - MeasureText(fighterName.c_str(), 8) - 5;
    }

    // Draw the border (optional)
    //DrawRectangleLines(position.x, position.y, width, height, borderColor);

    // check if name is empty
    if (fighterName.empty())
    {
        return;
    }
    // otherwise draw the fighter's name above the health bar
    DrawText(fighterName.c_str(), namePosX, position.y - 12, 8, borderColor);
}

void Lifebar::Update(int newHealth)
{
    currentHealth = newHealth;
    if (currentHealth < 0)
        currentHealth = 0; // Prevent negative health
}
