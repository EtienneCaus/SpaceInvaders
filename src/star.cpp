#include "star.h"

Star::Star(int positionX, int positionY) : Object()
{
    this->positionX = rand()%positionX;
    this->positionY = rand()%positionY;
    
    speed = rand()%10+10;
    texture.loadFromFile("lib/bullet.png");  
    sprite.setTexture(texture);
    sprite.setColor(sf::Color::White);
    sprite.setTextureRect(sf::IntRect(0,0,1,1));
    sprite.scale(10,10);
}

void Star::move(int value)
{
    positionY += speed;
    if(positionY > value)
        positionY=0;
}