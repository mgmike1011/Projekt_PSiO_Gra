#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
// Stworzone klasy
#include "enemy.h"
#include "player.h"
#include "bullet.h"

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
    sf::Text punkty_c;
    sf::Font czcionka_c;
    // ### Bufor do napisow
    std::stringstream ss;
    // ### Tekstury
    std::map<std::string,sf::Texture*> Textury_c,Textury_c2,Textury_c3;
    sf::Texture tekstura_przeciwnika;
    // ### Gwiezdny pyl - element ozdobny do imitacji ruchu
    sf::Vertex pyl_c[750];
    // ### Pociski
    std::vector<bullet*> pociski;
    // ### Punkty
    int Punkty=0;
    // ### Gracz
    Player* gracz;
    // ### Przeciwnicy
    float czas_miedzy_przeciwnikami = 40;
    std::vector<Enemy*> Przeciwnicy;
    // ### Pasek zdrowia
    sf::RectangleShape pasek_zdrowa,pasek_zdrowia_max;
    // ### Dzwieki
    sf::SoundBuffer pocisk, zderzenie_buffer,trafienie_buffer;
    sf::Sound pocisk_s,zderzenie_dzwiek,trafienie_dzwiek;
    // ### Muzyka
    sf::Music muzyka;

public:
    //settery i gettery
    void setPause(bool wybor);
    bool getPause();
    // --- Konstruktory
    Game();
    // --- Destruktor
    virtual ~Game();
    // --- Update
    void update_game();
    // --- Run
    void run();
    // --- Rysowanie
    void draw_game();
    void draw_game_napisy();
    void draw_game_tlo();
    // --- Metody Update poszczegolnych klas
    void update_akcja();
    void update_przeciwnicy();
    void update_pociski();
    void update_kolizja();
    void update_tlo();
    void update_napisy();
    void sterowanie();
    void update_Events();//w run
};

#endif // GAME_H
