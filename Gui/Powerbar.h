#ifndef GBFIGHTER_POWERBAR_H
#define GBFIGHTER_POWERBAR_H

#include "raylib.h"
#include <iostream>
#include <string>


class Powerbar
{
public:
    Powerbar(Vector2 pos,
             int height,
             int width,
             int maxValue,
             Color color,
             int playerNumber,
             bool drawReversed,
             std::string name = "");
    ~Powerbar();

    void Draw();
    void ChangeValue(int newHealth);

private:
    void _calculateNamePosX();

private:
    Vector2 position;
    int width;
    int height;
    int currentValue;
    int maxValue;
    Color barColor;
    Color borderColor;
    std::string fighterName;
    int playerNumber;
    float namePosX;
    bool drawReversed;
};

#endif //GBFIGHTER_POWERBAR_H
