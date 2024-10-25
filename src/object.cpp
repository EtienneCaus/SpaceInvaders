#include "object.h"

void Object::setPosition(int x, int y)
{
    positionX = x;
    positionY = y;
}
void Object::move(int x, int y)
{
    positionX += x;
    positionY += y;
}

sf::Sprite Object::draw()
{
    sprite.setPosition(positionX,positionY);
    return sprite;
}