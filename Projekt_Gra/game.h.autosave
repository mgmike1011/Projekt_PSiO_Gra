#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include "enemy.h"
class Game : public sf::RenderWindow
{
public:
    // --- Konstruktory
    Game();
    Game(sf::String);
    // ### Tło
    sf::Texture backgroundtx_c;
    sf::RectangleShape background_c;
    // ### Czas
    sf::Clock clock_c; //zegrar gry
    sf::Time time_c; //czas gry
    // ### Pauza
    bool pauza = true;
    // ### Napisy
    sf::Text koncowy_c;
    sf::Text czas_c;
    static sf::Font czcionka_c;
    // ### Bufor do konwersji danych
    std::stringstream ss;
    // ### Statki przeciwnika
    std::vector<Enemy> Enemy_c;
    // ### Gwiezdny pyl
    sf::Vertex pyl_c[750];
    // --- Uruchamianie
    void run();
    // --- Koniec gry
    // funkcje dodać!
    // --- Wykrywanie kolizji
    bool Kolizja(const std::vector<sf::Vector2f>&,const sf::Vector2f&);
    bool Kolizja(const sf::Transform &,const std::vector<sf::Vector2f>&,const sf::Vector2f&);
    // --- Aktualizacja przeciwnikow
    void update(Game &);
};

#endif // GAME_H
