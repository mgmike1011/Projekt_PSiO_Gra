#include "player.h"

Player::Player()
{
    Spowolnienie = SpowolnienieMax;
    hp = hpMax;
    //Zaladowanie grafiki
    if(!tekstura.loadFromFile("resources/Gracz/playerShip1_red.png"))
    {
        std::cout<<"Nie udalo sie zadalowac grafiki gracza"<<std::endl;
    }
    this->setTexture(tekstura);
    this->setPosition(600,710-tekstura.getSize().y);
}

int Player::gethp()
{
    return this->hp;
}

int Player::getHpMax()
{
    return hpMax;
}

void Player::sethp(int &i)
{
    hp = i;
}

void Player::minushp(int &i)
{
    if(hp>0)
    {
        hp=hp-i;
    }
    if(hp<0)
    {
        hp=0;
    }
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
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    //{
    //    this->shoot();

    //}
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

void Player::update_player()
{
    if(Spowolnienie<SpowolnienieMax)
    {
        Spowolnienie = Spowolnienie+3;
    }
}

void Player::draw_player(sf::RenderTarget *trg)
{
    trg->draw(*this);
}

sf::RectangleShape Player::getpasek_zdrowia()
{
    return  pasek_zdrowia;
}

void Player::addPoint_forplayer()
{
    punkty++;
}

void Player::Poruszanie(float &kierunek_x_, float &kierunek_y_)
{
    this->move(speed*kierunek_x_,speed*kierunek_y_);
}
