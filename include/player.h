#pragma once
#include "bullet.h"

struct Player : public Object
{
    Player();
    bool checkColision(Object* bullet);
};