#include <SFML/Audio.hpp>
#include <list>
#include "player.h"
#include "alien.h"
#include "star.h"

using namespace sf;

bool RUNNING = true;
int SPEED = 0;
const int STAR_AMMOUNT = 40;
const int WINDOW_HEIGHT = VideoMode::getDesktopMode().height;
const int WINDOW_WIDTH = VideoMode::getDesktopMode().width;
RenderWindow window(VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Space Invaders", Style::Fullscreen);

Text text;
Font font;
SoundBuffer beep, beep2;
Sound sound;

Star* stars[STAR_AMMOUNT];
Player player;
std::list<Alien*> aliens;
std::list<Bullet*> bullets; //liste des balles ennemies
Bullet* playerBullet = NULL; //la balle du joueur

char timer=0;

void FillScreen()
{
    for(int x=0; x<WINDOW_WIDTH-150; x=x+150)
        for(int y=0; y<WINDOW_HEIGHT/2; y=y+160)
            aliens.push_back(new Alien(x,y));
}

int main()
{
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(1000);

    font.loadFromFile("lib/raster.ttf");   
    text.setFont(font);
    text.setCharacterSize(52);
    text.setStyle(Text::Bold);
    text.setFillColor(Color::White);

    beep.loadFromFile("lib/beep-02.wav");
    beep2.loadFromFile("lib/beep-03.wav");

    while(window.isOpen())
    {
        Event event;
        window.clear();
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }

        if(SPEED == 0)
        {
            text.setString("PRESS ESC TO QUIT\n\nPRESS RMB TO BEGIN\n\nUSE THE MOUSE TO MOVE\nLMB TO SHOOT");
            if(Mouse::isButtonPressed(Mouse::Right))
            {
                for(int s=0; s<STAR_AMMOUNT; s++)
                    stars[s] = new Star(WINDOW_WIDTH, WINDOW_HEIGHT);
                FillScreen();
                SPEED=4;
                text.setString("SPEED : " + std::to_string(SPEED));
            }
        }
        else if(RUNNING)
        {
            
            player.setPosition(sf::Mouse::getPosition().x-(player.size[0]/2) ,WINDOW_HEIGHT - player.size[1]);
            if(timer>10)
            {
                if(Mouse::isButtonPressed(Mouse::Left) && playerBullet == NULL)
                   playerBullet = new Bullet(player.positionX + player.size[0]/2 , player.positionY , true);
                else if(playerBullet)
                {
                    if(SPEED<10)
                        playerBullet->move(10);
                    else
                        playerBullet->move(SPEED);
                    for(Alien* a : aliens)
                        if(a->checkColision(playerBullet))
                        {
                            sound.setBuffer(beep);
                            sound.play();
                            aliens.remove(a);
                            delete a;
                            playerBullet->positionY = -player.size[1];
                            break;
                        }
                    if(playerBullet->checkPosition())
                        playerBullet = NULL;
                }
                for(Alien* a : aliens)
                {
                    if(a->direction)
                        if(a->positionX+SPEED <= WINDOW_WIDTH-a->size[0])
                            a->move(SPEED);
                        else
                            a->changeDirection();
                    else
                        if(a->positionX-SPEED >= 0)
                            a->move(-SPEED);
                        else
                            a->changeDirection();
                    if(a->positionY > WINDOW_HEIGHT-a->size[1])
                        RUNNING = false;
                    if(bullets.size() < 3 && rand()%aliens.size() == aliens.size()-1)
                        bullets.push_back(new Bullet(a->positionX + a->size[0]/2 , a->positionY , false));
                }
                for(Bullet* b : bullets)
                {
                    b->move(SPEED);
                    if(player.checkColision(b))
                        {
                            sound.setBuffer(beep2);
                            sound.play();
                            if(text.getColor() == Color::White)
                                text.setColor(Color::Green);
                            else if(text.getColor() == Color::Green)
                                text.setColor(Color::Yellow);
                            else if(text.getColor() == Color::Yellow)
                                text.setColor(Color::Red);
                            else RUNNING=false;
                            bullets.remove(b);
                            delete b;
                            break;
                        }
                    if(b->checkPosition(WINDOW_HEIGHT))
                    {
                        bullets.remove(b);
                        delete b;
                        break;
                    }
                }
                for(Star* s : stars)
                    s->move(WINDOW_HEIGHT);

                timer=0;
                if(aliens.empty())
                {
                    for(Bullet* b : bullets)
                    delete b;
                    bullets.clear();
                    FillScreen();
                    SPEED++;
                    text.setString("SPEED : " + std::to_string(SPEED));
                }
            }
            else
                timer++;
        }
        else
        {
            sound.setBuffer(beep2);
            sound.play();
            text.setString("SPEED : " + std::to_string(SPEED) + "\t\tGAME OVER!!\n\nPRESS RMB TO RETRY");
            window.draw(text);
            if(Mouse::isButtonPressed(Mouse::Right))
            {
                SPEED=4;
                text.setColor(Color::White);
                text.setString("SPEED : " + std::to_string(SPEED));
                playerBullet=NULL;
                for(Alien* a : aliens)
                    delete a;
                aliens.clear();
                for(Bullet* b : bullets)
                    delete b;
                bullets.clear();
                FillScreen();
                RUNNING=true;
            }
        }
        
        if(SPEED > 0)
        {
            for(Star* s : stars)
                window.draw(s->draw());
            for(Bullet* b : bullets)
                window.draw(b->draw());
            for(Alien* a : aliens)
                window.draw(a->draw());
            if(playerBullet != NULL)
                window.draw(playerBullet->draw());
            window.draw(player.draw());
        }
        window.draw(text);
        window.display();
    }
    return 0;
}