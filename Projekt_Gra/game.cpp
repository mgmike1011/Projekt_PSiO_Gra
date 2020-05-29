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
    czcionka_c.loadFromFile("dd.tft");
    if(!czcionka_c.loadFromFile("dd.tft"))
    {
        std::cout<<"Blad wczytania czcionki"<<std::endl;
    }
    this->koncowy_c.setFont(czcionka_c);
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
    // Gwiezdny pyl
    for(auto &el : pyl_c)
    {
        el.position = sf::Vector2f(rand()%800,rand()%600);
        el.color = sf::Color(100,100,100);
    }
}

void Game::run()
{
    sf::Time time = clock_c.getElapsedTime();
    // Incjacja gracza
    Player gracz;
    // Wydarzenia
    sf::Event event;
    while(this->isOpen())
    {
        while(this->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) //Zamykanie okna
            {
                this->close();
            }
            if(event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                if(pauza)
                {
                    pauza = false;
                } else
                {
                    pauza = true;
                }
            }
        }
        // Koniec czasu
//        if(gracz.hp>0&&time_c.asSeconds()<=0)
//        {
//              gracz.hp=0;
//              gracz.zniszcz = false;
//        }
        if(pauza)
        {
            this->clear(sf::Color::Black);
            this->draw(background_c);
            this->display();
            continue;
        }
        // Przeciwnicy
        if(gracz.gethp()>0)
        {
            Enemy_c.emplace_back(Enemy());
        }
    }
}
