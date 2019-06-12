//
// Created by semyon on 11.06.19.
//


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "map.h"
#include <time.h>

using namespace sf;

const int winSizeX= 800;
const int winSizeY = 600;
float speed = 0.3f;
float ballSpeed = 0.3f;
const double PI = 3.1415922653;
int score = 0;
bool gameover = false;


class Ball {
protected:
    sf::CircleShape shape;
    float posX, posY;
    float radius;
    sf::RenderWindow * window;


public:
    bool isCollis;
    float speedY;
    float speedX;
    Ball(sf::RenderWindow * window) {
        this->window = window;
        this->posX =rand()%window->getSize().x+radius;
        this->posY = this->window->getSize().y / 2;
        this->radius = 10;
        this->speedY = 0.1f;
        if(posX > window->getSize().x/2) {
            this->speedX =-0.15f;
        } else {
            this->speedX = 0.15f;
        }
        this->shape.setPosition(posX,posY);
        this->shape.setRadius(this->radius);
        this->shape.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
        this->isCollis = false;

    }


    int getRadius() {
     return this->radius;
    }

    sf::FloatRect getRect() {
        return sf::FloatRect(posX, posY, radius, radius);
    }




    void update(float time,sf::RectangleShape shape)
    {

        if(getRect().intersects(sf::FloatRect(shape.getPosition().x,shape.getPosition().y-radius,shape.getSize().x,shape.getSize().y)))
        {
          speedY = -speedY;
        }
        this->posY +=speedY*time;
        this->posX += speedX * time;
        this->shape.setPosition(posX,posY);
        if(posX+speedX > window->getSize().x - radius) {
            speedX = -speedX;
            if(rand()%(1-10) >= 5) {
                speedY = -speedY;
            } else {
                speedY = speedY;
            }
        }
        if(posX +speed < 3) {
            speedX =-speedX;
            if(rand()%(1-10) >= 5) {
                speedY = speedY;
            } else {
                speedY = -speedY;
            }
        }


    }




    void render()
    {
     this->window->draw(this->shape);
    }
};




int main()
{
    srand(time(0));
    // окно
    RenderWindow window(VideoMode(winSizeX,winSizeY),"Breakout");
    Texture texture;
    texture.loadFromFile("../res/block.png");
    window.setFramerateLimit(65);
    window.setMouseCursorVisible(false);

    std::cout << "Enter escape for exit"<<std::endl;

   //TODO: игрок
 RectangleShape player;
 player.setSize(Vector2f(100,15));
 player.setPosition(winSizeX/2-player.getSize().x,winSizeY/2+(winSizeY/100*30));
 player.setFillColor(Color::White);


 //TODO: картинка gameover-а
 RectangleShape gameoverShape;
 Texture gameoverTexture;
 gameoverTexture.loadFromFile("../res/gameover.jpg");
 gameoverShape.setTexture(&gameoverTexture);
 gameoverShape.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));

//TODO: Текст для очков
Text text;
sf::Font font;
font.loadFromFile("../fonts/font.ttf");
text.setFont(font);
text.setPosition(10,10);
text.setCharacterSize(35);
std::string str = "Score: " + std::to_string(score);
text.setString(str);


RectangleShape rect;
rect.setSize(Vector2f(40,20));
rect.setTexture(&texture);


SoundBuffer buffer;
buffer.loadFromFile("../sounds/beep.ogg");
Sound sound;
sound.setBuffer(buffer);




Ball ball(&window);

Clock clock;

while(window.isOpen())
{
    double time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time /800;
    Event event;
    while(window.pollEvent(event))
    {
        if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();
    }





    //UPDATE
    ball.update(time,player);




    // --------------------------

    //управление движеним платформы
    if(!gameover) {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.move(-speed * time, 0);
        } else if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.move(speed * time, 0);
        }
    }

   //очистка экрана
    window.clear(sf::Color::Black);



    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {



            if(TileMap[i][j] == '0') {
                rect.setPosition(j * 40, i * 20);

                if(ball.getRect().intersects(sf::FloatRect(rect.getPosition().x,rect.getPosition().y,rect.getSize().x,rect.getSize().y)))
                {
                    TileMap[i][j] = ' ';
                    ball.isCollis = true;
                    ball.speedY = -ball.speedY;
                    if(rand()%(1-10)>= 5) {
                        ball.speedX = -ball.speedX;
                    } else {
                        ball.speedX = ball.speedX;
                    }
                    score++;
                    std::string str = "Score: " + std::to_string(score);
                    text.setString(str);
                    sound.play();
                }
            if(!gameover) {
                window.draw(rect);
            }

            }

            if(ball.getRect().top + ball.getRadius() > window.getSize().y) {
                gameover =true;
                window.draw(gameoverShape);
                window.draw(text);
            }





    }
    if(!gameover) {
        window.draw(player);//рисуем игрока
        ball.render();//рисуем мячик
    }
     window.display(); //отрисовываем экран
}

return 0;
}