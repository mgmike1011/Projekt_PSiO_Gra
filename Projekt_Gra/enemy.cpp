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

Enemy::Enemy() :sf::ConvexShape()
{
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
    srand(time((NULL)));
    int los = rand()%3;
    switch (los)
    {
    case 0 :
        setTexture(tekstury[0]);
        rotate(90);
        break;
    case 1 :
        setTexture(tekstury[1]);
        rotate(90);
        break;
    case 2 :
        setTexture(tekstury[2]);
        rotate(90);
        break;
    }
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
        }else{
            kill_c=true;
        }
        hit_c=false;
    }
    setPosition(getPosition().x-speed_c,getPosition().y+kierunek_c);
}
