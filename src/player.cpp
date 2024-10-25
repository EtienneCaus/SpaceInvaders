#include "player.h"

Player::Player() : Object()
{
    texture.loadFromFile("lib/player.png");    
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,11,8));
    sprite.scale(10,10);
    sprite.setColor(sf::Color::Green);
}

bool Player::checkColision(Object* bullet)
{
    if(positionX < bullet->positionX && positionX + size[0] > bullet->positionX &&
        positionY < bullet->positionY + bullet->size[1] && 
            positionY + size[1] > bullet->positionY + bullet->size[1])
        return true;
    return false;
}