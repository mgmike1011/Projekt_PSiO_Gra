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
        el.color = sf::Color::White;
    }
    // Przypisanie czcionki
    if(!czcionka_c.loadFromFile("resources/Czcionki/OpenSans-Bold.ttf"))
    {
        std::cout<<"Blad wczytania czcionki"<<std::endl;
    }
    this->koncowy_c.setFont(czcionka_c); //dla napisu koncowego
    koncowy_c.setPosition(560,360);
    koncowy_c.setCharacterSize(30);
    koncowy_c.setFillColor(sf::Color::White);
    koncowy_c.setStyle(sf::Text::Bold);
    this->czas_c.setFont(czcionka_c); //dla czasu
    czas_c.setPosition(150,10);
    czas_c.setCharacterSize(23);
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

    sf::Time tpause;
    sf::Clock zegar;
    while(this->isOpen())
    {
        sf::Event event;
        while(this->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) //Zamykanie okna
            {
                this->close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                {
                    if(pauza == true)
                    {
                        pauza = false;
                        std::cout<<"Gra wznowiona."<<std::endl;
                    } else
                    {
                        pauza = true;
                        std::cout<<"Pauza gry, by kontynuwoac wcisnij przycisk \"p\"."<<std::endl;
                    }
                }
            }
        }
        sf::Time elapsed = zegar.restart();

        if(pauza==true)
        {
            this->clear(sf::Color::Black);
            this->draw(background_c);
            this->display();
            clock_c.restart();
            tpause = time_c;
            continue;
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
        // Przeciwnicy
        if(gracz.gethp()>0)
        {
            if(!rand()%30){
                Enemy_c.emplace_back(Enemy());
            }
        }
        if(pauza == false)
        {
            gracz.animate(elapsed);
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
            update_gry();
        }
        if(gracz.gethp()<0)
        {
            gameover(gracz);
        }
        //draw(gracz);
        this->draw_player(gracz);
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

bool Game::Kolizja(const std::vector<sf::Vector2f> &vec1, const sf::Vector2f &vec2)
{
    //Algorytm przeksztalca kazdy kolejny bok figury jako wektor ma po swojej prawej stronie punkt
    int jest=-1;
    float a,b,c,d,e;
    for(size_t i=0;i<vec1.size();i++)
    {
        a = vec1[i].x;
        b = vec1[i].y;
        if(i+1==vec1.size())
        {
            c=vec1[0].x;
        } else {
            c=vec1[i+1].x;
        }
        if(i+1==vec1.size())
        {
            d=vec1[0].x;
        } else {
            d=vec1[i+1].x;
        }
        e = (vec2.x-a)*(d-b)-(vec2.y-b)*(c-a);
        if(e!=-1)
        {
            if(jest==-1)
            {
                jest=e>0;
            } else if ((d>0)!=jest) {
                return false;
            }
        }
    }
    return true;
}

void Game::update_gry()
{
    for(auto it = Enemy_c.begin();it!=Enemy_c.end();it++)
    {
        if(it->getPosition().x<0||it->getPosition().y<-20||it->getifkill())
        {
            Enemy_c.erase(it);
        }
        it->update();
        this->draw(*it);
    }
}

void Game::update_player(Player &gracz)
{
    // Aktualizacja stanu zdrowia i paska stanu zdrowia
    if(gracz.gethp()>0)
    {
        gracz.pasek_zdrowia.setSize(sf::Vector2f(gracz.gethp(),10));
        for (auto &el: Enemy_c)
        {
            if(el.getGlobalBounds().left<=gracz.getGlobalBounds().left+gracz.getGlobalBounds().width &&gracz.getGlobalBounds().intersects(el.getGlobalBounds()))
            {
                bool stoop = false;
                for(auto & pkt:gracz.getPunktykolizji())
                {
                    sf::Vector2f p(pkt);
                    float x = gracz.getTexture()->getSize().x/2;
                    float y = gracz.getTexture()->getSize().y/2;
                    if(Kolizja(el.getwierzcholki(),sf::Vector2f(gracz.getPosition().x-x+p.x,gracz.getPosition().y-y+p.y)))
                    {
                        el.setkill(true);
                        gracz.sethp(gracz.gethp()-el.getPointCount());
                        stoop = true;
                        break;
                    }
                }
                if(stoop)
                {
                    break;
                }
            }
        }
        // Aktualizacja stanu pociskow
        for(auto &el:gracz.getpociski())
        {
            update_bullet(el,gracz);
        }
        for(auto it =  gracz.pociski.begin();it!=gracz.pociski.end();it++)
        {
            if(it->getifkill()||it->getPosition().x>1300)
            {
                gracz.pociski.erase(it);
            }
        }
    }
}
    void Game::draw_player(Player &gracz)
    {
        update_player(gracz);
        this->draw(gracz);
        if(gracz.gethp()>0)
        {
            this->draw(gracz.getpasek_zdrowia());
        }
        for(auto &el : gracz.getpociski())
        {
            this->draw(el);
        }
        this->draw(gracz.tekst_hp);
        this->draw(gracz.tekst_c);
    }

    void Game::update_bullet(bullet &pocisk, Player &gracz)
    {
        pocisk.move(pocisk.getspeed(),0);
        // Trafienia
        for(auto &el : Game::Enemy_c)
        {
            //if(pocisk.getGlobalBounds().intersects(el.getGlobalBounds()) && Kolizja(el.getTransform(),el.getwierzcholki(),el.getPosition()))
            if(pocisk.getGlobalBounds().intersects(el.getGlobalBounds()) && Kolizja(el.getwierzcholki(),el.getPosition()))
            {
                el.sethit(true);
                pocisk.setkill(true);
                if(gracz.gethp()>0)
                {
                    gracz.addPoint_forplayer();
                }
            }
        }
    }
