#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player :public sf::ConvexShape
{
private:
    //
    int hp;
    int punkty;
public:
    Player();
    int gethp();
    void rysuj();
    int getPunkty();
};

#endif // PLAYER_H
