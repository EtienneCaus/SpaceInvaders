#pragma once
#include "object.h"

struct Star : public Object
{
    int speed;
    Star(int positionX, int positionY);
    void move(int value);
};