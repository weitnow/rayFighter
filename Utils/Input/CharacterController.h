// CharacterController.h
#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

struct CharacterController
{
    bool moveLeft = false;
    bool moveRight = false;
    bool jump = false;
    bool duck = false;
    bool punch = false;
    bool kick = false;
    bool block = false;
    // general input
    bool key_esc = false;
    bool key_enter = false;
    bool key_q = false;
};

#endif // CHARACTER_CONTROLLER_H
