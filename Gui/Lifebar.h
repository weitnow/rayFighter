#ifndef GBFIGHTER_LIFEBAR_H
#define GBFIGHTER_LIFEBAR_H

#include "raylib.h"
#include <iostream>
#include <string>


class Lifebar
{
public:
    // Constructor to initialize the lifebar with int maxHp
    Lifebar(Vector2 pos, int height, int width, int maxHp, Color color, Color border, std::string name)
        : position(pos), height(height), width(width), currentHealth(maxHp), maxHealth(maxHp), barColor(color),
          borderColor(border), fighterName(name)
    {
    }

    // Draw the lifebar
    void Draw()
    {
        // Calculate the width of the health bar based on the current health
        float healthPercentage = static_cast<float>(currentHealth) / static_cast<float>(maxHealth);
        float currentBarWidth = width * healthPercentage;

        // Draw the actual health bar
        DrawRectangle(position.x, position.y, static_cast<int>(currentBarWidth), height, barColor);

        // Draw the border (optional)
        DrawRectangleLines(position.x, position.y, width, height, borderColor);

        // (Optional) Draw the fighter's name above the health bar
        // DrawText(fighterName.c_str(), position.x, position.y - 10, 4, BLACK);
    }

    // Update the health bar with new health value (int)
    void Update(int newHealth)
    {
        currentHealth = newHealth;
        if (currentHealth < 0)
            currentHealth = 0; // Prevent negative health
    }

    // Reset the health back to full
    void Reset()
    {
        currentHealth = maxHealth;
    }

private:
    Vector2 position;
    int width;
    int height;
    int currentHealth;
    int maxHealth;
    Color barColor;
    Color borderColor;
    std::string fighterName;
};

#endif //GBFIGHTER_LIFEBAR_H
