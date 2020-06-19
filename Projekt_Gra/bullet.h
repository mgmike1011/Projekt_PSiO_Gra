#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <iostream>
class bullet : public sf::Sprite
{
private:
    // Tekstura zostanie zaladowana na poczatku programu i przypisana na stale
    // ### Predkosc
    float speed = 15;
    // ### Kill
    bool kill = false;
    // ### Kierunek poruszania sie
    sf::Vector2f kierunek;
public:
    // --- Konstruktor
    bullet(sf::Texture *tekstura,float pozycja_x,float pozycja_y, float kierunek_x_, float kierune_y_);
    // --- Do sprawdzania kolizji
    const sf::FloatRect getBounds() const;
    // --- settery i gettery
    float getspeed();
    void setkill(bool statement);
    bool getifkill();
    // --- Update pocisku
    void update_bullet_();
    // --- Wyswietlanie
    void draw_bullet(sf::RenderTarget * trg);
    // --- Destruktor
    virtual ~bullet();
};

#endif // BULLET_H
