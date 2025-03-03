#include "Gui.h"
#include "../Game/Game.h"

Gui::Gui(Game* game) : game(game), timer(99), winningPoint1(0), winningPoint2(0), power1(0), power2(0)
{
    lifebar1 = new Powerbar(Vector2{23, 26}, 5, 100, 10, Constants::RAYFIGHTER_ROSA, 1, false, "Andy");
    lifebar2 = new Powerbar(Vector2{132, 26}, 5, 100, 10, Constants::RAYFIGHTER_ROSA, 2, false, "Zangief");

    powerbar1 = new Powerbar(Vector2{23, 138}, 5, 50, 3, Constants::RAYFIGHTER_ROSA, 1, true);
    powerbar2 = new Powerbar(Vector2{182, 138}, 5, 50, 3, Constants::RAYFIGHTER_ROSA, 2, true);


    //Load the bgUpperGui animation
    bgUpperGui = game->asepriteManager->getAnimFile("bgUpperGui");
    bgUpperGui->setFrameTag("bgUpperGui-Idle");

    //Load the bgLowerGui animation
    bgLowerGui = game->asepriteManager->getAnimFile("bgLowerGui");
    bgLowerGui->setFrameTag("bgLowerGui-Idle");

    //Load the winningPoint graphics
    winningPoint = game->asepriteManager->getAnimFile("bg16SpriteCollection");

    lastUpdateTime = GetTime();
}

Gui::~Gui()
{
    // Clean up resources if necessary
    delete lifebar1;
    delete lifebar2;
    lifebar1 = nullptr;
    lifebar2 = nullptr;

    delete powerbar1;
    powerbar1 = nullptr;
    delete powerbar2;
    powerbar2 = nullptr;

    delete bgUpperGui;
    delete bgLowerGui;
    delete winningPoint;
}

void Gui::draw()
{
    // Draw a white rectangle for UpperGui
    DrawRectangle(0, 0, 256, 40, BLACK);

    // Draw a black rectangle for LowerGui
    DrawRectangle(0, 136, 256, 8, BLACK);

    // Draw the lifebars
    lifebar1->Draw();
    lifebar2->Draw();
    powerbar1->Draw();
    powerbar2->Draw();

    // Draw the bgUpperGui
    bgUpperGui->drawCurrentSelectedTag(0, 0, 1, WHITE);
    DrawText(std::to_string(timer).c_str(), 122, 11, 8, Constants::RAYFIGHTER_LIGHTROSA);

    _drawWinningPoints(winningPoint1, 1);
    _drawWinningPoints(winningPoint2, 2);

    // Draw the bgLowerGui
    bgLowerGui->drawCurrentSelectedTag(0, 136, 1, WHITE);
    _drawPowSymbol();
}

void Gui::update(float deltaTime)
{
    // Update the bgUpperGui
    bgUpperGui->update(deltaTime);

    // Update the bgLowerGui
    bgLowerGui->update(deltaTime);

    // Update the timer
    if (GetTime() - lastUpdateTime > 1)
    {
        timer--;
        lastUpdateTime = GetTime();
    }
}

void Gui::setLife1(int life)
{
    lifebar1->ChangeValue(life);
}

void Gui::setLife2(int life)
{
    lifebar2->ChangeValue(life);
}

void Gui::setPower1(int power) // max power is 4
{

    power1 = power;

    if (power > 3)
        powerbar1->ChangeValue(3);
    else
        powerbar1->ChangeValue(power);
}

void Gui::setPower2(int power)
{
    power2 = power;

    if (power > 3)
        powerbar2->ChangeValue(3);
    else
        powerbar2->ChangeValue(power);
}

void Gui::setWinningPoint1(int point)
{
    winningPoint1 = point;
}

void Gui::setWinningPoint2(int point)
{
    winningPoint2 = point;
}

void Gui::_drawWinningPoints(int winningPoints, int playerNumber)
{
    int x1 = 0;
    int x2 = 0;

    if (playerNumber == 1)
    {
        x1 = 23;
        x2 = 29;
    }
    else
    {
        x1 = 229;
        x2 = 223;
    }

    // Draw the winningPoint
    if (winningPoints > 0)
    {
        if (winningPoints > 1)
        {
            // draw the second winningpoint
            winningPoint->drawFrame("bg16SpriteCollection-WinningPoint", x2, 6, 1, WHITE);
        }
        // draw the first winningpoint
        winningPoint->drawFrame("bg16SpriteCollection-WinningPoint", x1, 6, 1, WHITE);
    }
}

void Gui::_drawPowSymbol()
{
    if (power1 < 3 && power2 < 3)
    {
        bgLowerGui->setFrameTag("bgLowerGui-Idle");
        return;
    }
    if (power1 == 4 && power2 == 4)
    {
        bgLowerGui->setFrameTag("bgLowerGui-Pow");
    }
    else if (power1 == 4)
    {
        bgLowerGui->setFrameTag("bgLowerGui-PowP1");
    }
    else if (power2 == 4)
    {
        bgLowerGui->setFrameTag("bgLowerGui-PowP2");
    }
}
