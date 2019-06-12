//
// Created by semyon on 11.06.19.
//


#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "map.h"
#include <time.h>

using namespace sf;

const int winSizeX= 800;
const int winSizeY = 600;
float speed = 0.3f;
float ballSpeed = 0.3f;
const double PI = 3.1415922653;

class Ball {
protected:
    sf::CircleShape shape;
    float posX, posY;
    float radius;
    sf::RenderWindow * window;


public:
    bool isCollis;
    float speed;
    Ball(sf::RenderWindow * window) {
        this->window = window;
        this->posX =rand()%window->getSize().x-shape.getRadius();
        this->posY = this->window->getSize().y / 2;
        this->radius = 10;
        this->speed = 0.1f;
        this->shape.setPosition(posX,posY);
        this->shape.setRadius(this->radius);
        this->shape.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
        this->isCollis = false;

    }



    sf::FloatRect getRect() {
        return sf::FloatRect(posX, posY, radius, radius);
    }




    void update(float time,sf::RectangleShape shape)
    {

        if(getRect().intersects(sf::FloatRect(shape.getPosition().x,shape.getPosition().y,shape.getSize().x,shape.getSize().y)))
        {

          speed = -speed;
        }
        this->posY +=speed*time;
        this->shape.setPosition(posX,posY);


    }




    void render()
    {
     this->window->draw(this->shape);
    }
};


int main()
{
    srand(time(0));
    //игрок (платформа)
 RectangleShape player;
 player.setSize(Vector2f(100,15));
 player.setPosition(winSizeX/2-player.getSize().x,winSizeY/2+(winSizeY/100*30));
 player.setFillColor(Color::White);


 //мяч
 /*CircleShape circleBall; //фигуру окружности
 float circleX,circleY; // ее позиции
 circleX = winSizeX/2;
 circleY = winSizeY/2;
 float ballSpeed = 0.15f; // скорость полета мяча
 sf::Color * color = new Color(rand()%255,rand()%255,rand()%255); // цвет мяча
 circleBall.setFillColor(*color); // устанавливаем цвет
circleBall.setRadius(13);
circleBall.setPosition(circleX,circleY);
*/

//return rect



RenderWindow window(VideoMode(winSizeX,winSizeY),"Breakout");
Texture texture;
texture.loadFromFile("../res/block.png");
RectangleShape rect;
rect.setSize(Vector2f(40,20));
rect.setTexture(&texture);


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

    //математика и обновление для мяча




    ball.update(time,player);

  /*  if(sf::FloatRect(player.getPosition().x,player.getPosition().y,player.getSize().x,player.getSize().y).intersects(sf::FloatRect(circleBall.getPosition().x,circleBall.getPosition().y+circleBall.getRadius(),circleBall.getRadius(),circleBall.getRadius()))) {
        circleY += player.getPosition().y;
        circleY += ballSpeed*time;
        circleBall.setPosition(circleX,circleY);
    } else {
       circleY += ballSpeed * time;
       circleBall.setPosition(circleX,circleY);
    }
*/
    //TODO: сдесь ошибка в том что нужно прибовлять к позиции speed * time  а не присваивать


    // --------------------------

    //control
    if(Keyboard::isKeyPressed(Keyboard::A)) {
         player.move(-speed*time,0);
    } else
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.move(speed*time,0);
    }


    window.clear();

    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {

            if(TileMap[i][j] == '0') {
                rect.setPosition(j * 40, i * 20);
                if(ball.getRect().intersects(sf::FloatRect(rect.getPosition().x,rect.getPosition().y,rect.getSize().x,rect.getSize().y))) {
                    TileMap[i][j] = ' ';
                    ball.isCollis = true;
                    ball.speed = -ball.speed;
                }

                window.draw(rect);

            }

    }

    window.draw(player);
  //  window.draw(circleBall);
     ball.render();
    window.display();
}

return 0;
}