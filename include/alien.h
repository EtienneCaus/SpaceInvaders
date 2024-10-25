#pragma once
#include "bullet.h"

struct Alien : public Object
{
    int changingPosition=0;
    bool direction=true;
    Alien(int positionX, int positionY);
    void changeDirection();
    void move(int value);
    bool checkColision(Bullet* bullet);
};