#include "alien.h"

Alien::Alien(int positionX, int positionY) : Object()
{
    this->positionX=positionX;
    this->positionY=positionY;
    
    texture.loadFromFile("lib/alien.png");    
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,11,8));
    sprite.scale(10,10);
}

void Alien::move(int value)
{
    if(changingPosition<=0)
        positionX += value;
    else
    {
        positionY += abs(value);
        changingPosition -= abs(value);
    }
}

void Alien::changeDirection()
{
    direction = !direction;
    changingPosition=size[1];
}

bool Alien::checkColision(Bullet* bullet)
{
    if(positionX < bullet->positionX && positionX + size[0] > bullet->positionX &&
        positionY < bullet->positionY && positionY + size[1] > bullet->positionY)
        return true;
    return false;
}