#include "game.h"
#include <time.h>


int main() {
    srand(time(NULL));
    sf::RenderWindow menu(sf::VideoMode(1280,720),"Space war");
    menu.setFramerateLimit(60);
    sf::Texture tlo,przycisk;
    if(!tlo.loadFromFile("resources/Menu/tlo_menu.png"))
    {
        std::cout<<"Nie udalo sie zaladowac grafiki tla menu"<<std::endl;
    }
    if(!przycisk.loadFromFile("resources/Menu/przycisk_graj.png"))
    {
        std::cout<<"Nie udalo sie zaladowac grafiki przycisku graj"<<std::endl;
    }
    sf::RectangleShape tlo_r,przycisk_r;
    tlo_r.setTexture(&tlo);
    tlo_r.setPosition(0,0);
    tlo_r.setSize(sf::Vector2f(1280,720));
    przycisk_r.setTexture(&przycisk);
    przycisk_r.setPosition(560,360);
    przycisk_r.setSize(sf::Vector2f(200,100));
    while(menu.isOpen())
    {
        sf::Event event;
        while (menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                menu.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button==sf::Mouse::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(menu);
                    if(przycisk_r.getGlobalBounds().contains(mouse_pos.x,mouse_pos.y))
                    {
                        menu.close();
                        Game Gra;
                        Gra.run();
                    }
                }
            }
        }
        menu.clear(sf::Color::Black);
        menu.draw(tlo_r);
        menu.draw(przycisk_r);
        menu.display();
    }
    return 0;
}
