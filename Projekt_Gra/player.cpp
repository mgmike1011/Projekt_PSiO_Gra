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
    if(!czcionka_c.loadFromFile("resources/Czcionki/OpenSans-Bold.ttf"))
    {
        std::cout<<"Blad wczytania czcionki"<<std::endl;
    }
    ss<<"Punkty: "<< punkty;
    tekst_c.setFont(czcionka_c);
    tekst_c.setFillColor(sf::Color::White);
    tekst_c.setStyle(sf::Text::Bold);
    tekst_c.setPosition(220,20);
    tekst_c.setString(ss.str());
    tekst_c.setCharacterSize(30);
    ss.str("");

    ss<<"HP: "<<hp;
    tekst_hp.setFont(czcionka_c);
    tekst_hp.setFillColor(sf::Color::White);
    tekst_hp.setStyle(sf::Text::Bold);
    tekst_hp.setPosition(300,20);
    tekst_hp.setString(ss.str());
    tekst_hp.setCharacterSize(30);
    ss.str("");
}

int Player::gethp()
{
    return this->hp;
}

int Player::getPunkty()
{
    return punkty;
}

void Player::shoot()
{
    pociski.emplace_back(bullet(sf::Vector2f(getPosition().x+getTexture()->getSize().x/2,getPosition().y+10)));
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

sf::RectangleShape Player::getpasek_zdrowia()
{
    return  pasek_zdrowia;
}

std::vector<bullet> Player::getpociski()
{
    return pociski;
}
