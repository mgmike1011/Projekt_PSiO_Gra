#include "game.h"

Game::Game()
{

}

Game::Game(sf::String nazwa_okna) : sf::RenderWindow(sf::VideoMode(800,600),nazwa_okna)
{
    this->setFramerateLimit(60);//ustawinie limitu klatek, 60, jak na nowej generacji konsol :)
    //this->setActive(true);
    //this->setVerticalSyncEnabled(true);
    // Przypisanie czcionki
    this->koncowy_c.setFont(Game::czcionka_c);
    koncowy_c.setPosition(133,200);
    koncowy_c.setCharacterSize(30);
    koncowy_c.setFillColor(sf::Color::Black);
    koncowy_c.setStyle(sf::Text::Bold);
    this->czas_c.setFont(Game::czcionka_c);
    czas_c.setPosition(150,30);
    czas_c.setCharacterSize(15);
    czas_c.setFillColor(sf::Color::Blue);
    czas_c.setStyle(sf::Text::Bold);
    // Czas
    time_c=sf::seconds(100);
    //tlo
    backgroundtx_c.loadFromFile("");
    if(!backgroundtx_c.loadFromFile(""))
    {
        std::cerr<<"Blad wczytania tekstury tla"<<std::endl;
    }
    background_c.setTexture(&backgroundtx_c);
    background_c.setPosition(0,0);
    background_c.setSize(sf::Vector2f(800,600));
}
