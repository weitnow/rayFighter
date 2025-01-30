#ifndef OPTION_SELECT_STATE_H
#define OPTION_SELECT_STATE_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/Core.h"
#include "BaseState.h"
#include "raylib.h"

class OptionSelectState : public BaseState
{
public:
    OptionSelectState(Game* game);
    ~OptionSelectState();
    void Enter() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Pause() override;
    void Resume() override;
    void Exit() override;
    void HandleInput() override;


private:
    AsepriteAnimationFile* OptionSelectScreen;
    Utils::CircularCounter selectedRow{
        0,
        5}; // 0 = Resolution, 1 = Music on/off, 2 = Sound Master Volume, 3 = Input P1, 4 = Input P2, 5 = Save

    int selectedResolution;
    bool musicOn;
    float soundMasterVolume; // from 0.0 to 1.0

    void calculate_circular_counter_fixed_param(int incrementl);
    int _getMaxValOfSelectedOption(); //depends on the selectedRow

    void saveConfigToFile();

    void _renderOptionMenu();
};

#endif
