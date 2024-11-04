#ifndef GBFIGHTER_LIFEBAR_H
#define GBFIGHTER_LIFEBAR_H

#include "raylib.h"
#include <iostream>
#include <string>


class Lifebar
{
public:
    // Constructor to initialize the lifebar with int maxHp
    Lifebar(Vector2 pos,
            int height,
            int width,
            int maxHp,
            Color color,
            Color border,
            std::string name,
            int playerNumber);
    ~Lifebar();

    void Draw();
    void Update(int newHealth);

private:
    Vector2 position;
    int width;
    int height;
    int currentHealth;
    int maxHealth;
    Color barColor;
    Color borderColor;
    std::string fighterName;
    int playerNumber;
};

#endif //GBFIGHTER_LIFEBAR_H
