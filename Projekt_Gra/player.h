#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

//Stworzone klasy
#include "bullet.h"

class Player : public sf::Sprite
{
private:
    // ### Predkosc
    float speed =150;
    // ### Punkty zdrowia
    int hp = 100;
    float punkty_paska_zdrowia = 50;
    // ### Zdobyte punkty
    int punkty =0;
    // ### Tekstura
    sf::Texture tekstura;
    // ### Parametr do wykrywania kolziji
    std::vector<sf::Vector2i> Punkty_kolizji;
    // ### Zniszczenie
    bool Zniszony = false;
    // ### Czcionka do punktow i punktow hp
public:
    sf::RectangleShape pasek_zdrowia;
    sf::Text tekst_c;
    sf::Text tekst_hp;
    sf::Font czcionka_c;
    // ### Napisy
    std::stringstream ss;
    // ### Pociski
    std::vector<bullet> pociski;
public:
    // --- Konstruktor
    Player();
    // --- gettery i settery
    std::vector<sf::Vector2i> getPunktykolizji();
    int gethp();
    void sethp(int i);
    int getPunkty();
    sf::RectangleShape getpasek_zdrowia();
    std::vector<bullet> getpociski();
    // --- Dodanie punktu
    void addPoint_forplayer();
    // --- Strzelanie
    void shoot();
    // --- Poruszanie
    void animate(const sf::Time &elapsed);
    //moze w main!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // --- Rysowanie gracza na ekranie i animacja
    //void rysuj(Game &);
    //przechwytywanie zdarzen
    //void catchEvents(sf::Events &)
    //metoda aktualizajci update
    //void uptade(Game &)
};

#endif // PLAYER_H
