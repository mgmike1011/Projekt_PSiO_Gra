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

void Player::animate(const sf::Time &elapsed)
{
    auto bounds = this->getGlobalBounds();
    float okres = elapsed.asSeconds();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(bounds.top>0)
        {
            move(0,-std::abs(speed)*okres);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(bounds.top+bounds.height<720)
        {
            move(0,std::abs(speed)*okres);
        }
    }
    //Mozliwosc pouszania sie troche do przodu i tylu - do przemyslenia
    /*
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(bounds.left+bounds.width <450)//1280
        {
            move(okres*std::abs(speed),0);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(bounds.left>0)
        {
            move(okres*-std::abs(speed),0);
        }
    }
    */
}
