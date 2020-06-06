#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

// Stworzone klasy
#include "enemy.h"
#include "player.h"


class Game : public sf::RenderWindow
{
private:
    // ### Tło
    sf::Texture backgroundtx_c;
    sf::RectangleShape background_c;
    // ### Czas
    sf::Clock clock_c; //zegrar gry
    sf::Time time_c; //czas gry
    // ### Pauza
    bool pauza = false;
    // ### Napisy
    sf::Text koncowy_c;
    sf::Text czas_c;
    sf::Font czcionka_c;
    // ### Bufor do napisow
    std::stringstream ss;
    // ### Statki przeciwnika
    std::vector<Enemy> Enemy_c;
    // ### Gwiezdny pyl - element ozdobny do imitacji ruchu
    sf::Vertex pyl_c[750];
public:
    //settery i gettery
    void setPause(bool wybor);
    bool getPause();
    // --- Konstruktory
    Game();
    Game(sf::String);
    // --- Uruchamianie
    void run();
    // --- Koniec gry
    void gameover(Player &gracz);
    // --- Wykrywanie kolizji
    bool Kolizja(const std::vector<sf::Vector2f>&,const sf::Vector2f&);
    bool Kolizja(const sf::Transform &,const std::vector<sf::Vector2f>&,const sf::Vector2f&);
    // --- Aktualizacja przeciwnikow
    void update(Game &);
};

#endif // GAME_H
