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
    int hpMax =100;
    float punkty_paska_zdrowia = 50;
    // ### Zdobyte punkty
    int punkty =0;
    // ### Tekstura
    sf::Texture tekstura;
    // ### Zniszczenie
    bool Zniszony = false;
    // ### Spowolnienie
    float Spowolnienie, SpowolnienieMax=5;
public:
    sf::RectangleShape pasek_zdrowia;
    sf::Text tekst_c;
    sf::Text tekst_hp;
    sf::Font czcionka_c;
    // ### Napisy
    std::stringstream ss;
public:
    // --- Konstruktor
    Player();
    // --- gettery i settery
    int gethp();
    int getHpMax();
    void sethp(int &i);
    void minushp(int &i);
    int getPunkty();
    sf::RectangleShape getpasek_zdrowia();
    // --- Dodanie punktu
    void addPoint_forplayer();
    // --- Strzelanie
    //void shoot();
    bool canshoot();
    // --- Poruszanie
    void Poruszanie(float &kierunek_x_,float &kierunek_y_);
    void animate(const sf::Time &elapsed);
    // --- Update
    void update_player();
    // --- Rysowanie na ekranie
    void draw_player(sf::RenderTarget *trg);
    // --- Wirtualny destruktor
    virtual ~Player();
};

#endif // PLAYER_H
