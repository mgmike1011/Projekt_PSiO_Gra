#include "player.h"

Player::Player()
{
    rotate(-90);
}

int Player::gethp()
{
    return this->hp;
}

int Player::getPunkty()
{
    return punkty;
}
