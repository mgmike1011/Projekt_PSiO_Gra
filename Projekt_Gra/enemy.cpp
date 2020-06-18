#include "enemy.h"

void Enemy::setTexture(sf::Texture tekstura_)
{
    Tekstura = tekstura_;
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

Enemy::Enemy(sf::Vector2f &pozycja)
{
    int zmienna = rand()%10+2;
    punkty_hpMax = zmienna;
    typ =0;
    punkty_hp = punkty_hpMax;
    damage_ = zmienna;
    Punkty_enemy = zmienna;
    //Ladowanie tekstury
    if(!Tekstura.loadFromFile("resources/Przeciwnik/playerShip3_blue.png"))
    {
        std::cout<<"Nie udalo sie zaladowac tekstury statku przeciwnika"<<std::endl;
    }
    //Ustawianie tekstury
    this->setTexture(Tekstura);
    //Ustwienia figury
    this->setRadius(25);
    this->setPointCount(5);
    this->setPosition(pozycja);
}


