#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include "bullet.h"
#include <iostream>

class Player : public sf::Sprite
{
private:
    // ### Predkosc
    float speed =0;
    // ### Punkty zdrowia
    int hp;
    sf::RectangleShape pasek_zdrowia;
    float punkty_paska_zdrowia = 50;
    // ### Zdobyte punkty
    int punkty;
    // ### Tekstura
    sf::Texture tekstura;
    // ### Parametr do wykrywania kolziji
    std::vector<sf::Vector2i> Punktykolizji;
    // ### Zniszczenie
    bool Zniszony = false;
    // ### Czcionka do punktow i punktow hp
    sf::Text czcionka_pkt_hp;
    // ### Napisy
    std::stringstream ss;
    // ### Pociski
    std::vector<bullet> pociski;
public:
    // --- Konstruktor
    Player();
    // --- gettery i settery
    int gethp();
    int getPunkty();
    // --- Rysowanie gracza na ekranie i animacja
    void rysuj();
    // --- Strzelanie
    void shoot();
};

#endif // PLAYER_H
