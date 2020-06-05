#include "game.h"

void Game::setPause(bool wybor)
{
    pauza=wybor;
}

bool Game::getPause()
{
    return pauza;
}


Game::Game() : sf::RenderWindow(sf::VideoMode(1280,720),"Space war")
{
    this->setFramerateLimit(60);//ustawinie limitu klatek, 60, jak na nowej generacji konsol :)
    this->setActive(true);
    //this->setVerticalSyncEnabled(false);
    //tlo
    backgroundtx_c.setRepeated(true);
    if(!backgroundtx_c.loadFromFile("resources/Tlo/tlo.png"))
    {
        std::cerr<<"Blad wczytania tekstury tla"<<std::endl;
    }
    backgroundtx_c.setSmooth(true);
    background_c.setTexture(&backgroundtx_c);
    background_c.setPosition(0,0);
    background_c.setSize(sf::Vector2f(1280,720));
    // Gwiezdny pyl
    srand(time(NULL));
    for(auto &el : pyl_c)
    {
        el.position = sf::Vector2f(rand()%1280,rand()%720);
        //el.color = sf::Color(155+rand()%100, 155+rand()%100, 155+rand()%100, 255);
        el.color = sf::Color::White;
    }
    // Przypisanie czcionki
    if(!czcionka_c.loadFromFile("resources/Czcionki/OpenSans-Bold.ttf"))
    {
        std::cout<<"Blad wczytania czcionki"<<std::endl;
    }
    this->koncowy_c.setFont(czcionka_c); //dla napisu koncowego
    koncowy_c.setPosition(133,200);
    koncowy_c.setCharacterSize(30);
    koncowy_c.setFillColor(sf::Color::White);
    koncowy_c.setStyle(sf::Text::Bold);
    this->czas_c.setFont(czcionka_c); //dla czasu
    czas_c.setPosition(150,20);
    czas_c.setCharacterSize(15);
    czas_c.setFillColor(sf::Color::White);
    czas_c.setStyle(sf::Text::Bold);
    // Czas
    time_c=sf::seconds(100);
}

void Game::run()
{
    // Incjacja gracza
    Player gracz;
    sf::Transform pyl_c_Move;//ruch pylu
    // Wydarzenia
    sf::Event event;
    sf::Time tpause;
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
            if(!pauza)
            {
                //Zabezpieczenie, ze podczas pauzy gracz nie  rusza sie
                //gracz.catchEvents(event);
            }
        }
        // Koniec czasu
        //        if(gracz.hp>0&&time_c.asSeconds()<=0)
        //        {
        //              gracz.hp=0;
        //              gracz.zniszcz = false;
        //        }
        /*
         *
         *
         */

        //test!!!!!!!
        //pauza=false;
        // !!!!!!!!!!!!!
        if(pauza)
        {
            this->clear(sf::Color::Black);
            this->draw(background_c);
            this->display();
            clock_c.restart();
            tpause = time_c;
            continue;
        }
        // Przeciwnicy
        if(gracz.gethp()>0)
        {
            if(!rand()%30){
                Enemy_c.emplace_back(Enemy());
            }
        }
        clear(sf::Color::Black);
        draw(background_c);
        //pyl gwiezdny - imersja ruchu
        draw(pyl_c,750,sf::PrimitiveType::Points);
        for(auto &el:pyl_c)
        {
            el.position.x = el.position.x -(rand()%3+1);
            if(pyl_c_Move.transformPoint(el.position).x<=0) //po wyjsciu za krawedz cofa je na sam poczatek
            {
                el.position.x = 1280;
            }
        }
        if(gracz.gethp()>0)
        {
            update(*this);
        }
        if(gracz.gethp()<0)
        {
            //gameover(&gracz);
        }
        //gracz.rysuj();
        //Wyswietlanie czasu
        ss.str("");
        ss <<"Czas: "<<std::abs((int) time_c.asSeconds()) << " sek.";
        czas_c.setString(ss.str());
        ss.str("");
        draw(czas_c);
        //Wyswietlenie na ekranie wszystkiego
        display();
        if (!pauza)
        {
            time_c = tpause - clock_c.getElapsedTime();
        }
    }
}

void Game::gameover(Player &gracz)
{
    ss<<"Udalo ci sie zdobyc : "<<gracz.getPunkty();
    koncowy_c.setString(ss.str());
    draw(koncowy_c);
}

void Game::update(Game &gra)
{
   for(auto it = Enemy_c.begin();it!=Enemy_c.end();it++)
   {
       if(it->getPosition().x<0||it->getPosition().y<-20||it->getifkill())
       {
           Enemy_c.erase(it);
       }
       it->update();
       gra.draw(*it);
   }
}
