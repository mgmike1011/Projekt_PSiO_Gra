#include "player.h"

Player::Player()
{
    //Zaladowanie grafiki
    if(!tekstura.loadFromFile("resources/Gracz/playerShip1_red.png"))
    {
        std::cout<<"Nie udalo sie zadalowac grafiki gracza"<<std::endl;
    }
    this->setTexture(tekstura);
    this->rotate(90);
    this->setPosition(tekstura.getSize().x,360);
    //Pasek HP
    pasek_zdrowia.setSize(sf::Vector2f(punkty_paska_zdrowia*100,10));
    pasek_zdrowia.setPosition(100,100);
    pasek_zdrowia.setFillColor(sf::Color::Red);
    pasek_zdrowia.setOutlineColor(sf::Color::White);
    pasek_zdrowia.setOutlineThickness(3);
    //Napisy
    ss<<"Punkty: "<< punkty;
}

int Player::gethp()
{
    return this->hp;
}

int Player::getPunkty()
{
    return punkty;
}
