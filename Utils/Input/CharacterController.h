// CharacterController.h
#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H
#include <string>

struct CharacterController
{
    bool moveLeft = false;
    bool moveRight = false;
    bool jump = false;
    bool duck = false;
    bool punch = false;
    bool kick = false;
    bool block = false;
    // specialmoves
    bool special1 = false;
    bool special2 = false;
    bool special3 = false;
    // overriden by BaseCharacter (if CharacterController is added as Composition to a BaseCharacter)
    bool isLeft = false; // true if the character is left of the other character, only valid for player1 or player2
    // general input
    bool key_esc = false;
    bool key_enter = false;
    bool key_q = false;
};

#endif // CHARACTER_CONTROLLER_H
