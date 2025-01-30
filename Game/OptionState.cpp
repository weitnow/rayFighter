#include "OptionState.h"
#include "../Constants.h"
#include "Game.h"
#include "GameState.h"

const char* resolutionOptions[] = {"640x480", "800x600", "1280x720", "1920x1080", "2560x1440", "3440x1440"};

OptionSelectState::OptionSelectState(Game* game)
    : BaseState(game), OptionSelectScreen(nullptr), selectedResolution{screen2DManager->getScreenResolution()},
      musicOn{soundManager->getBgMusicOn()}, soundMasterVolume{soundManager->getMasterVolume()}
{
    OptionSelectScreen = game->asepriteManager->getAnimFile("optionSelectScreen");
    OptionSelectScreen->setFrameTag("optionSelectScreen-Intro");
}

OptionSelectState::~OptionSelectState()
{
    std::cout << "CharSelectState Destructor called, unloading resources" << std::endl;

    game->soundManager->unloadMusic("sunburn.mp3");

    delete OptionSelectScreen;
}

void OptionSelectState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    game->soundManager->loadMusic("sunburn.mp3", 1.f);
    game->soundManager->playBackgroundMusic("sunburn.mp3");

    screen2DManager->fadeEffect(0.6f, 0.f);
}

void OptionSelectState::Update(float deltaTime)
{

    // Update OptionSelectScreen
    OptionSelectScreen->update(deltaTime);

    if (OptionSelectScreen->getCurrentFrame() == OptionSelectScreen->getMaxFrame())
    {
        OptionSelectScreen->setFrameTag("optionSelectScreen-Idle");
    }

    HandleInput();
}

void OptionSelectState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(GREEN);

    // Draw OptionSelectScreen
    OptionSelectScreen->drawCurrentSelectedTag(0, 0);

    // Draw availabe Screenresolution
    _renderOptionMenu();

    screen2DManager->draw();

    game->screen2DManager->endDrawToRenderTarget();


    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    ClearBackground(BLACK);
    game->screen2DManager->beginDrawToScreen();

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    // render overlay
    game->screen2DManager->drawOverlay();

    game->screen2DManager->endDrawToScreen();
}

void OptionSelectState::Pause()
{
}

void OptionSelectState::Resume()
{
}


void OptionSelectState::Exit()
{
}

void OptionSelectState::HandleInput()
{
    if (player1Controller->jump && inputHandler->isKeyJustPressed(*player1Controller)) // up
    {
        selectedRow.decrement();
    }
    else if (player1Controller->duck && inputHandler->isKeyJustPressed(*player1Controller)) // down
    {
        selectedRow.increment();
    }

    if (player1Controller->moveRight && inputHandler->isKeyJustPressed(*player1Controller)) // right
    {
        calculate_circular_counter_fixed_param(1);
    }
    else if (player1Controller->moveLeft && inputHandler->isKeyJustPressed(*player1Controller)) // left
    {
        calculate_circular_counter_fixed_param(-1);
    }


    if (player1Controller->kick)
    {
        //pop this state and return to menu
        game->PopState();
    }
    else if (player1Controller->punch || player2Controller->punch)
    {

        if (selectedRow.get_value() != 5)
        {
            selectedRow.set_value(5);
        }
        else
        {
            soundManager->setBgMusicOn(musicOn);
            soundManager->setMasterVolume(soundMasterVolume);

            ScreenResolution res = static_cast<ScreenResolution>(selectedResolution);
            screen2DManager->changeScreenResolution(res);

            saveConfigToFile();
        }
    }
}

void OptionSelectState::calculate_circular_counter_fixed_param(int increment)
{

    switch (selectedRow.get_value())
    {
    case 0: //0 = Resolution
        selectedResolution =
            Utils::calculate_circular_counter<int>(selectedResolution, increment, 0, _getMaxValOfSelectedOption());
        break;
    case 1: // 1 = Music on/off,
        musicOn = Utils::calculate_circular_counter<int>(musicOn, increment, 0, _getMaxValOfSelectedOption());
        break;
    case 2: // 2 = Sound Master Volume
    {
        float incrementf = static_cast<float>(increment) / 10;
        incrementf = std::round(incrementf * 10) /
                     10; // this rounds everything to onDecimal after . -> for example 0.10001 is 0.1
        soundMasterVolume = Utils::calculate_circular_counter<float>(soundMasterVolume,
                                                                     incrementf,
                                                                     0,
                                                                     _getMaxValOfSelectedOption(),
                                                                     true); // true = limit bounds
        break;
    }
    case 3: // 3 = Input P1
        break;
    case 4: // 4 = Input P2
        break;
    default:
        break;
    }
}

int OptionSelectState::_getMaxValOfSelectedOption() //depends on the selectedRow
{
    switch (selectedRow.get_value())
    {
    case 0: //0 = Resolution
        return 5;
    case 1: // 1 = Music on/off,
        return 1;
    case 2: // 2 = Sound Master Volume
        return 1;
    case 3: // 3 = Input P1
        return 0;
    case 4: // 4 = Input P2
        return 0;
    default:
        return 0;
    }
}

void OptionSelectState::saveConfigToFile()
{
    screen2DManager->saveScreenResolution();
    soundManager->saveSoundConfig();
}

void OptionSelectState::_renderOptionMenu()
{
    static const int indentcol1 = 40;
    static const int indentcol2 = 120;
    int xValueFirstElement = 60;
    static const int spacer = 10;
    static const int volumebarLenght = 50;

    Color color = (selectedRow.get_value() == 0) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("Resolution", indentcol1, xValueFirstElement, 8, color);
    DrawText(resolutionOptions[selectedResolution], indentcol2, xValueFirstElement, 8, color);

    color = (selectedRow.get_value() == 1) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("Music", indentcol1, xValueFirstElement += spacer, 8, color);
    DrawText((musicOn) ? "on" : "off", indentcol2, xValueFirstElement, 8, color);

    color = (selectedRow.get_value() == 2) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("Mastervolume", indentcol1, xValueFirstElement += spacer, 8, color);
    // Draw the background of the volume bar
    static const Rectangle volumeBar = {indentcol2,
                                        xValueFirstElement + 1,
                                        volumebarLenght,
                                        8}; // Pos and Size of the volumebar
    DrawRectangleRec(volumeBar, Constants::RAYFIGHTER_LIGHTBROWN);
    // Draw the filled portion representing the current volume level
    DrawRectangle(volumeBar.x,
                  volumeBar.y,
                  volumeBar.width * soundMasterVolume,
                  volumeBar.height,
                  Constants::RAYFIGHTER_DARKBROWN);

    color = (selectedRow.get_value() == 3) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("P1 Input", indentcol1, xValueFirstElement += spacer, 8, color);

    color = (selectedRow.get_value() == 4) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("P2 Input", indentcol1, xValueFirstElement += spacer, 8, color);

    color = (selectedRow.get_value() == 5) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("Save", indentcol1, xValueFirstElement += spacer, 8, color);
}
