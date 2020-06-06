#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
class Enemy : public sf::ConvexShape
{
private:
    // ### Tekstury
    std::vector<sf::Texture> tekstury;
    // ### Śmierć
    bool kill_c = false;
    // ### trafienie
    bool hit_c = false;
    // ### Prędkość
    float speed_c;
    // ### Kierunek
    float kierunek_c;
    // ### Zmienna do trafien
    std::vector<sf::Vector2f> wierzcholki;
public:
    // --- settery i gettery
    void setTexture(sf::Texture);
    bool getifkill();
    bool getifhit();
    // --- Konstrutor
    Enemy();
    // --- akturalizacja stanu
    void update();
};

#endif // ENEMY_H
