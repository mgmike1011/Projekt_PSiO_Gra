#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player :public sf::ConvexShape
{
private:
    //
    int hp;
public:
    Player();
    int gethp();
};

#endif // PLAYER_H
