#include "bullet.h"

bullet::bullet(const sf::Vector2f &vec) : sf::RectangleShape()
{
    sf::Texture tekstura2;
    if(!tekstura2.loadFromFile("resources/Pociski/laserBlue02.png"))
    {
        std::cout<<"Nie udalo sie zaladowac tekstury pocisku niebieskiego"<<std::endl;
    } else
    {
        tekstura.emplace_back(tekstura2);
    }
    if(!tekstura2.loadFromFile("resources/Pociski/laserGreen04.png"))
    {
        std::cout<<"Nie udalo sie zaladowac tekstury pocisku niebieskiego"<<std::endl;
    } else
    {
        tekstura.emplace_back(tekstura2);
    }
    if(!tekstura2.loadFromFile("resources/Pociski/laserRed02.png"))
    {
        std::cout<<"Nie udalo sie zaladowac tekstury pocisku niebieskiego"<<std::endl;
    } else
    {
        tekstura.emplace_back(tekstura2);
    }
    int indeks = rand()%2;
    setTexture(&tekstura[indeks]);
    setSize(sf::Vector2f(37,13));
    setPosition(vec.x,vec.y);
}

float bullet::getspeed()
{
    return speed;
}
void  bullet::setkill(bool statement)
{
    kill = statement;
}

bool bullet::getifkill()
{
    return kill;
}

void bullet::animate_bullet(const sf::Time &elapsed)
{
    //auto bounds = this->getGlobalBounds();
    float okres = elapsed.asSeconds();
    sf::RectangleShape::move(speed*okres,0);
}
