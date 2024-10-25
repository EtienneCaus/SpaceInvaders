#pragma once
#include "object.h"

struct Bullet : public Object
{
    bool direction=false;
    Bullet(int positionX, int positionY, bool direction);
    void move(int value);
    bool checkPosition();
    bool checkPosition(int value);
};