#ifndef BULLET_H
#define BULLET_H
#include "SFML/Graphics.hpp"

class bullet : public sf::ConvexShape
{
private:
    // ### Teketura
    sf::Texture tekstura;
    // ### Predkosc
    float speed = 5;
    // ### Kill
    bool kill = false;
public:
    bullet();
    void update();
};

#endif // BULLET_H
