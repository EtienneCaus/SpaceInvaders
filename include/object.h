#pragma once
#include <SFML/Graphics.hpp>

struct Object
{
    sf::Texture texture;
    int positionX=0;
    int positionY=0;
    int size[2]={110,80};
    sf::Sprite sprite;
    void setPosition(int x, int y);
    void move(int x, int y);
    sf::Sprite draw();
};