#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <iostream>
class bullet : public sf::RectangleShape
{
private:
    // ### Teketura
    std::vector<sf::Texture> tekstura;
    // ### Predkosc
    float speed = 5;
    // ### Kill
    bool kill = false;
    // ###
public:
    // --- Konstruktor
    bullet(const sf::Vector2f&);

    //moze w main !!!!!!!!!!!!!!!!!!!!
    //void update(game &);
};

#endif // BULLET_H
