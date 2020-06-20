#include "enemy.h"

void Enemy::setTexture(sf::Texture tekstura_)
{
    Tekstura = tekstura_;
}

bool Enemy::getifkill()
{
    return kill_c;
}

int &Enemy::getPoints()
{
    return this->Punkty_enemy;
}

int &Enemy::getDamage()
{
    return this->damage_;
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
    int zmienna = rand()%8+3;
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
    setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
    this->setTexture(Tekstura);
    //Ustwienia figury
    this->setPosition(pozycja);
    this->setSize(sf::Vector2f(98,75));
}

Enemy::Enemy(sf::Vector2f &pozycja, sf::Texture tekstura_)
{
    int zmienna = rand()%8+3;
    punkty_hpMax = zmienna;
    typ =0;
    punkty_hp = punkty_hpMax;
    damage_ = zmienna;
    Punkty_enemy = zmienna;
    //Ustawianie tekstury
    this->setTexture(tekstura_);
    //Ustwienia figury
    this->setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
    this->setPosition(pozycja);
    this->setSize(sf::Vector2f(50,50));
    //rotate(90);
}

void Enemy::draw_enemy(sf::RenderTarget *trg)
{
    trg->draw(*this);
}

const sf::FloatRect Enemy::getBounds() const
{
    return this->getGlobalBounds();
}

void Enemy::update_enemy()
{
    this->move(0,speed_c);
}

Enemy::~Enemy() {}


