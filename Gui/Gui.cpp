#include "Gui.h"
#include "../Game/Game.h"

Gui::Gui(Game* game)
    : game(game), timer(99), winningPoint1(0), winningPoint2(0), power1(0), power2(0), state(nullptr), initDone(false)
{


    //Load the bgUpperGui animation
    bgUpperGui = game->asepriteManager->createNewAnimFilePtr("bgUpperGui-Idle");

    //Load the bgLowerGui animation
    bgLowerGui = game->asepriteManager->createNewAnimFilePtr("bgLowerGui-Idle");

    //Load the winningPoint graphics
    winningPoint = game->asepriteManager->createNewAnimFilePtr("bg16SpriteCollection");

    lastUpdateTime = GetTime();
}

Gui::~Gui()
{
    // Clean up resources if necessary

    if (initDone)
    {
        delete lifebar1;
        delete lifebar2;
        lifebar1 = nullptr;
        lifebar2 = nullptr;

        delete powerbar1;
        powerbar1 = nullptr;
        delete powerbar2;
        powerbar2 = nullptr;
    }

    delete bgUpperGui;
    delete bgLowerGui;
    delete winningPoint;

    bgUpperGui = nullptr;
    bgLowerGui = nullptr;
    winningPoint = nullptr;
    this->game = nullptr;
    this->state = nullptr;
}

void Gui::init(BaseState* state)
{
    this->state = state;

    lifebar1 = new Powerbar(Vector2{23, 26},
                            5,
                            100,
                            state->player1->getMaxLife(),
                            Constants::RAYFIGHTER_ROSA,
                            1,
                            false,
                            state->player1->getObjName());
    lifebar2 = new Powerbar(Vector2{132, 26},
                            5,
                            100,
                            state->player2->getMaxLife(),
                            Constants::RAYFIGHTER_ROSA,
                            2,
                            false,
                            state->player2->getObjName());

    powerbar1 =
        new Powerbar(Vector2{23, 138}, 5, 50, state->player1->getMaxPowerLevel(), Constants::RAYFIGHTER_ROSA, 1, true);
    powerbar2 =
        new Powerbar(Vector2{182, 138}, 5, 50, state->player2->getMaxPowerLevel(), Constants::RAYFIGHTER_ROSA, 2, true);

    initDone = true;
}

void Gui::draw()
{
    if (!initDone)
    {
        return;
    }

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
    if (!initDone)
    {
        return;
    }

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

    // Update the lifebars
    setLife1(state->player1->getCurrentLife());
    setLife2(state->player2->getCurrentLife());

    // Update the powerbars
    setPower1(state->player1->getPowerLevel());
    setPower2(state->player2->getPowerLevel());
}

void Gui::setLife1(int life)
{
    lifebar1->ChangeValue(life);
}

void Gui::setLife2(int life)
{
    lifebar2->ChangeValue(life);
}

void Gui::setPower1(int power)
{
    power1 = power;
    powerbar1->ChangeValue(power);
}

void Gui::setPower2(int power)
{
    power2 = power;
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
    if (power1 < state->player1->getMaxPowerLevel() - 1 && power2 < state->player2->getMaxPowerLevel() - 1)
    {
        bgLowerGui->setFrameTag("bgLowerGui-Idle");
        return;
    }
    if (power1 == state->player1->getMaxPowerLevel() && power2 == state->player2->getMaxPowerLevel())
    {
        bgLowerGui->setFrameTag("bgLowerGui-Pow");
    }
    else if (power1 == state->player1->getMaxPowerLevel())
    {
        bgLowerGui->setFrameTag("bgLowerGui-PowP1");
    }
    else if (power2 == state->player2->getMaxPowerLevel())
    {
        bgLowerGui->setFrameTag("bgLowerGui-PowP2");
    }
}
