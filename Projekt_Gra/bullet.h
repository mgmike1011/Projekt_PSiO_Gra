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
    float speed = 150;
    // ### Kill
    bool kill = false;
    // ###
public:
    // --- Konstruktor
    bullet(const sf::Vector2f&);
    // --- settery i gettery
    float getspeed();
    void setkill(bool statement);
    bool getifkill();
    void animate_bullet(const sf::Time &elapsed);
    //moze w game !!!!!!!!!!!!!!!!!!!!
    //void update(game &);
};

#endif // BULLET_H
