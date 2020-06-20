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
    this->setVerticalSyncEnabled(false);
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
    for(auto &el : pyl_c)
    {
        el.position = sf::Vector2f(rand()%1280,rand()%720);
        el.color = sf::Color(155+rand()%100, 155+rand()%100, 155+rand()%100, 255);
    }
    // Przypisanie czcionki
    if(!czcionka_c.loadFromFile("resources/Czcionki/OpenSans-Bold.ttf"))
    {
        std::cout<<"Blad wczytania czcionki"<<std::endl;
    }
    if(!tekstura_przeciwnika.loadFromFile("resources/Przeciwnik/meteorGrey_big2.png"))
    {
        std::cout<<"Blad Tekstury przeciwnika"<<std::endl;
    }
    // Ladowanie tekstury dla pociskow
    Textury_c["Pocisk"] = new sf::Texture();
    Textury_c["Pocisk"]->loadFromFile("resources/Pociski/laserBlue02.png");
    Textury_c2["Pocisk"] = new sf::Texture();
    Textury_c2["Pocisk"]->loadFromFile("resources/Pociski/laserGreen04.png");
    Textury_c3["Pocisk"] = new sf::Texture();
    Textury_c3["Pocisk"]->loadFromFile("resources/Pociski/laserRed03.png");
    // Ustawienia napisow
    punkty_c.setPosition(sf::Vector2f(1100,680));
    punkty_c.setFont(czcionka_c);
    punkty_c.setFillColor(sf::Color::White);
    punkty_c.setCharacterSize(25);
    punkty_c.setString("Punkty");
    // Napis konca gry
    koncowy_c.setFont(czcionka_c);
    koncowy_c.setPosition(sf::Vector2f(470,300));
    koncowy_c.setFillColor(sf::Color::Red);
    koncowy_c.setOutlineColor(sf::Color::White);
    koncowy_c.setOutlineThickness(2);
    koncowy_c.setCharacterSize(60);
    koncowy_c.setString("Koniec gry!!!");
    // Status zycia (pasek zdrowia)
    pasek_zdrowa.setSize(sf::Vector2f(400,50));
    pasek_zdrowa.setOutlineColor(sf::Color::White);
    pasek_zdrowa.setOutlineThickness(2);
    pasek_zdrowa.setFillColor(sf::Color::Red);
    pasek_zdrowa.setPosition(sf::Vector2f(10,10));
    pasek_zdrowia_max = pasek_zdrowa;
    pasek_zdrowia_max.setFillColor(sf::Color::Black);
    gracz = new Player;
    if(!pocisk.loadFromFile("resources/Dzwieki/laser1.ogg"))
    {
        std::cout<<"Blad ladowanie dzwieku wystrzalu"<<std::endl;
    }
    pocisk_s.setBuffer(pocisk);
    pocisk_s.setVolume(75);
    if(!zderzenie_buffer.loadFromFile("resources/Dzwieki/twoTone2.ogg"))
    {
        std::cout<<"Blad ladowanie dzwieku kolizji"<<std::endl;
    }
    zderzenie_dzwiek.setBuffer(zderzenie_buffer);
    zderzenie_dzwiek.setVolume(90);
    if(!muzyka.openFromFile("resources/Muzyka/Quarkstar_-_Space_Fiction.ogg"))
    {
        std::cout<<"Blad ladowanie muzyki"<<std::endl;
    }
    muzyka.setVolume(50);
    if(!trafienie_buffer.loadFromFile("resources/Dzwieki/zapTwoTone2.ogg"))
    {
        std::cout<<"Blad ladowanie dzwieku trafienia"<<std::endl;
    }
    trafienie_dzwiek.setVolume(15);
    trafienie_dzwiek.setBuffer(trafienie_buffer);
}

Game::~Game()
{
    delete gracz;
    for(auto *el : Przeciwnicy)
    {
        delete el;
    }
    for(auto &el : Textury_c)
    {
        delete el.second;
    }
    for(auto *el : pociski)
    {
        delete el;
    }
}

void Game::update_game()
{
    this->sterowanie();
    gracz->update_player();
    update_kolizja();
    update_pociski();
    update_przeciwnicy();
    update_akcja();
    update_napisy();
    update_tlo();
}

void Game::run()
{
    // Wydarzenia
    sf::Time tpause;
    sf::Clock zegar;
    muzyka.play();
    while(this->isOpen())
    {
        sf::Event event;
        while(this->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) //Zamykanie okna
            {
                this->close();
            }
        }
        if(gracz->gethp()>0)
        {
            this->update_game();
        }

        this->draw_game();
    }
}

void Game::draw_game()
{
    this->clear(sf::Color::Black);
    this->draw_game_tlo();
    gracz->draw_player(*this);
    for(auto *el : pociski)
    {
        el->draw_bullet(this);
    }
    for(auto *el : Przeciwnicy)
    {
        el->draw_enemy(this);
    }
    this->draw_game_napisy();
    if(gracz->gethp()<=0)
    {
        this->draw(koncowy_c);
    }
    this->display();
}

void Game::draw_game_napisy()
{
    this->draw(punkty_c);
    this->draw(pasek_zdrowia_max);
    this->draw(pasek_zdrowa);
}

void Game::draw_game_tlo()
{
    sf::Transform pyl_c_Move;//ruch pylu
    this->draw(background_c);
    this->draw(pyl_c,750,sf::PrimitiveType::Points);
    for(size_t i =0;i<750;i++)
    {
        pyl_c[i].position.x = pyl_c[i].position.x -(i%2+1);
        if(pyl_c_Move.transformPoint(Game::pyl_c[i].position).x<=0) //po wyjsciu za krawedz cofa je na sam poczatek
        {
            pyl_c[i].position = sf::Vector2f(1280,pyl_c[i].position.y);
        }
    }
}

void Game::update_akcja()
{
    for(size_t i =0;i<Przeciwnicy.size();i++)
    {
        bool likwidacja = false;
        for(size_t j = 0; j<pociski.size() && likwidacja==false;j++ )
        {
            if(Przeciwnicy[i]->getGlobalBounds().intersects(pociski[j]->getGlobalBounds()))
            {
                trafienie_dzwiek.play();
                Punkty+=Przeciwnicy[i]->getPoints();
                delete Przeciwnicy[i];
                Przeciwnicy.erase(Przeciwnicy.begin()+i);
                delete pociski[j];
                pociski.erase(pociski.begin()+j);
                likwidacja=true;
            }
        }
    }
}

void Game::update_przeciwnicy()
{
    czas_miedzy_przeciwnikami+=1;
    if(czas_miedzy_przeciwnikami>=20)
    {
        sf::Vector2f pozycja(rand()%1200,-20);
        Przeciwnicy.emplace_back(new Enemy(pozycja,tekstura_przeciwnika));
        czas_miedzy_przeciwnikami=0;
    }
    size_t ile =0;
    for(auto *el : Przeciwnicy)
    {
        el->update_enemy();
        auto bounds = el->getGlobalBounds();
        if(bounds.top>720)
        {
            delete Przeciwnicy.at(ile);
            Przeciwnicy.erase(Przeciwnicy.begin()+ile);
        }
        else if (bounds.intersects(gracz->getGlobalBounds()))
        {
            gracz->minushp(Przeciwnicy.at(ile)->getDamage());
            delete  Przeciwnicy.at(ile);
            Przeciwnicy.erase(Przeciwnicy.begin()+ile);
            zderzenie_dzwiek.play();
        }
        ile++;
    }
}

void Game::update_pociski()
{
    size_t miejsce =0;
    for(auto *el : pociski)
    {
        el->update_bullet_();
        auto bounds =el->getGlobalBounds();
        if(bounds.top+bounds.height<0)
        {
            delete pociski.at(miejsce);
            pociski.erase(pociski.begin()+miejsce);
        }
        ++miejsce;
    }
}

void Game::update_kolizja()
{
    //Na podobe funkcji bounce z zajec
    auto bounds = gracz->getGlobalBounds();
    if(bounds.left<0)
    {
        gracz->setPosition(0,bounds.top);
    }
    else if(bounds.left+bounds.width>1279)
    {
        gracz->setPosition(1280-bounds.width,bounds.top);
    }
    if(bounds.top<0)
    {
        gracz->setPosition(bounds.left,0);
    }
    else if(bounds.top+bounds.height>719)
    {
        gracz->setPosition(bounds.left,720-bounds.height);
    }
}

void Game::update_tlo()
{
    sf::Transform pyl_c_Move;//ruch pylu
    draw(pyl_c,750,sf::PrimitiveType::Points);
    for(auto &el:pyl_c)
    {
        el.position.y = el.position.y -(rand()%3+1);
        if(pyl_c_Move.transformPoint(el.position).y<=1290) //po wyjsciu za krawedz cofa je na sam poczatek
        {
            el.position.y = 0;
        }
    }
}

void Game::update_napisy()
{
    std::stringstream ss;
    ss<<"Punkty : "<<Punkty;
    punkty_c.setString(ss.str());
    float rzut = gracz->gethp();
    float stan_zdrowia = rzut/gracz->getHpMax();
    pasek_zdrowa.setSize(sf::Vector2f(400*stan_zdrowia,50));
}

void Game::sterowanie()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->gracz->move(-5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->gracz->move(5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->gracz->move(0, -5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->gracz->move(0, 5);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&gracz->canshoot())
    {
        int randomowa = rand()%3;
        if(randomowa==0){
            pociski.emplace_back(new bullet(Textury_c["Pocisk"],gracz->getPosition().x+40,gracz->getPosition().y,0,-1));
            pocisk_s.play();
        }
        if(randomowa==1)
        {
            pociski.emplace_back(new bullet(Textury_c2["Pocisk"],gracz->getPosition().x+40,gracz->getPosition().y,0,-1));
            pocisk_s.play();
        }
        if(randomowa==2)
        {
            pociski.emplace_back(new bullet(Textury_c3["Pocisk"],gracz->getPosition().x+40,gracz->getPosition().y,0,-1));
            pocisk_s.play();
        }
    }
}



