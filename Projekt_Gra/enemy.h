#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
class Enemy : public sf::CircleShape
{
private:
    // ### Tekstura
    sf::Texture Tekstura;
    int typ;
    // ### Śmierć
    bool kill_c = false;
    // ### trafienie
    bool hit_c = false;
    // ### Prędkość
    float speed_c = 5;
    // ### Kierunek
    float kierunek_c;
    // ### Punkty zdrowia
    int punkty_hp;
    int punkty_hpMax;
    // ### Uszkodzenie
    int damage_;
    // ### Punkty
    int Punkty_enemy;
public:
    // --- settery i gettery
    void setTexture(sf::Texture tekstura_);
    bool getifkill();
    int &getPoints();
    int &getDamage();
    bool getifhit();
    void sethit(bool statement);
    void setkill(bool statement);
    // --- Konstrutor
    Enemy(sf::Vector2f & pozycja);
    // --- Wyswietlanie na ekranie
    void draw_enemy(sf::RenderTarget * trg);
    // --- Granice obiektu
    const sf::FloatRect getBounds() const;
    // --- aktualizacja stanu
    void update_enemy();
    // --- Wirtualny destruktor
    virtual ~Enemy();
};

#endif // ENEMY_H
