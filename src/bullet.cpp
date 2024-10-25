#include "bullet.h"

Bullet::Bullet(int positionX, int positionY, bool direction) : Object()
{
    this->positionX=positionX;
    this->positionY=positionY;
    this->direction=direction;

    texture.loadFromFile("lib/bullet.png");    
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,1,8));
    sprite.scale(10,10);

    if(!direction)
        sprite.setColor(sf::Color::Red);
}

void Bullet::move(int value)
{
    if(direction)
        positionY -= value;
    else
        positionY += value;
}

bool Bullet::checkPosition()
{
    if(positionY < -size[1])
        return true;
    return false;
}
bool Bullet::checkPosition(int value)
{
    if(positionY > value)
        return true;
    return false;
}