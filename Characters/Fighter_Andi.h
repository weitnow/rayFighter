//
// Created by weitnow on 12/24/23.
//

#ifndef GBFIGHTER_FIGHTER_ANDI_H
#define GBFIGHTER_FIGHTER_ANDI_H

#include "BaseCharacter.h"


class Fighter_Andi : public BaseCharacter {
public:
    Fighter_Andi(float x, float y);
    ~Fighter_Andi();
    void update(float deltaTime);
    void draw();


};


#endif //GBFIGHTER_FIGHTER_ANDI_H
