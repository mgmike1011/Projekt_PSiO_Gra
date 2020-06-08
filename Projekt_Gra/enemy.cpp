#include "enemy.h"

void Enemy::setTexture(sf::Texture tekstura)
{
    tekstury.emplace_back(tekstura);
}

bool Enemy::getifkill()
{
    return kill_c;
}

bool Enemy::getifhit()
{
    return hit_c;
}

void Enemy::sethit(bool statement)
{
    hit_c = statement;
}

void Enemy::setkill(bool statement)
{
    kill_c = statement;
}

std::vector<sf::Vector2f> Enemy::getwierzcholki()
{
    return wierzcholki;
}

Enemy::Enemy() :sf::ConvexShape()
{
    int hp =2;
    speed_c = rand()%5+1;
    kierunek_c= 360/(rand()%6+1);
    setPosition(1333,rand()%720+10);
    sf::Texture tx;
    if(!tx.loadFromFile("resources/Przeciwnik/playerShip3_blue.png"))
    {
        std::cout<<"Nie udalo sie zaladowac tekstury statku przeciwnika"<<std::endl;
    }else
    {
        tekstury.emplace_back(tx);
    }
    if(!tx.loadFromFile("resources/Przeciwnik/playerShip3_green.png"))
    {
        std::cout<<"Nie udalo sie zaladowac tekstury statku przeciwnika"<<std::endl;
    }else
    {
        tekstury.emplace_back(tx);
    }
    if(!tx.loadFromFile("resources/Przeciwnik/playerShip3_orange.png"))
    {
        std::cout<<"Nie udalo sie zaladowac tekstury statku przeciwnika"<<std::endl;
    }else
    {
        tekstury.emplace_back(tx);
    }
    int los = rand()%3;
    switch (los)
    {
    case 0 :
        setTexture(tekstury[0]);
        rotate(-90);
        break;
    case 1 :
        setTexture(tekstury[1]);
        rotate(-90);
        break;
    case 2 :
        setTexture(tekstury[2]);
        rotate(-90);
        break;
    }
    setPoint(0,sf::Vector2f(getPosition().x,getPosition().y+100/speed_c));
    wierzcholki.emplace_back(getPoint(0));
    setPoint(1,sf::Vector2f(getPosition().x,getPosition().y+100/speed_c));
    wierzcholki.emplace_back(getPoint(1));

    setPosition(1500,rand()%720);
}

void Enemy::update()
{
    if(hit_c)
    {
        if(getPointCount()>2)
        {
            move(30,0);
            speed_c=speed_c*1.2;
            setPointCount(getPointCount()-1);
            wierzcholki.pop_back();
        }else{
            kill_c=true;
        }
        hit_c=false;
    }
    setPosition(getPosition().x-speed_c,getPosition().y+kierunek_c);
}
