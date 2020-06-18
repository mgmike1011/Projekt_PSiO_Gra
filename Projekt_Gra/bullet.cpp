#include "bullet.h"


bullet::bullet(sf::Texture *tekstura, const sf::Vector2f &pozycja, float kierunek_x_, float kierune_y_, float speed_)
{
    this->setTexture(*tekstura);
    this->setPosition(pozycja);
    kierunek.x=kierunek_x_;
    kierunek.y = kierune_y_;
    speed = speed_;
}

const sf::FloatRect bullet::getBounds() const
{
    // Zwraca granice obiektu
    sf::FloatRect granice = this->getGlobalBounds();
    return granice;
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

void bullet::update_bullet_()
{
    //Ruch bedzie nastepowal z kazdym wywolaniem
    this->move(speed*kierunek.x,speed*kierunek.y);
}

void bullet::draw_bullet(sf::RenderTarget *trg)
{
    //Wyswietlanie na ekranie
    trg->draw(*this);
}

bullet::~bullet() {}
