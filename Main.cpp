#include "Main.h"
#include "Map.h"
#include "Besucher.h"
#include "Spieler.h"
#include "Events.h"

#include <iostream>
#include <memory>
#include <ctime>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    bool allCorrect = true;
    int winner = -1;
    int *score;
    int elapsedTicks = 0;
    std::shared_ptr<std::vector<sf::Texture>> textures;
    textures = std::make_shared<std::vector<sf::Texture>>(4);

    if( !(*textures)[TEXTURES::AGGRO].loadFromFile("data/skull.png"))
        std::cerr << "can't load Textture data/skull.png" << std::endl;
    if( !(*textures)[TEXTURES::BAD_REACTION].loadFromFile("data/biohazard.png"))
        std::cerr << "can't load Textture data/biohazard.png" << std::endl;
    if( !(*textures)[TEXTURES::GOOD_REACTION].loadFromFile("data/sun.png"))
        std::cerr << "can't load Textture data/sun.png" << std::endl;
    if( !(*textures)[TEXTURES::MERCHANT].loadFromFile("data/foodball.png"))
        std::cerr << "can't load Textture data/foodball.png" << std::endl;

    srand(time(NULL));
    const sf::Color cBACKGROUND(0x60, 0x60, 0x60);//);
    std::default_random_engine unrealEngine;
    std::normal_distribution<double> gaussCharisma( 4, 1.2);
    std::normal_distribution<double> gaussFandom(0.2, 0.2);

    int playerNum = 3;

    sf::Font font;
    if (!font.loadFromFile("data/LinLibertine_R.otf")) {
        std::cerr << "Couldn‘t load font from ‘data/LinLibertine_R.otf’" << std::endl;
        return EXIT_FAILURE;
    }
    std::shared_ptr<std::vector<Spieler>> spieler;
    std::shared_ptr<std::vector<Besucher>> besucher;
    std::shared_ptr<sf::RenderWindow> window;
    playerNum = splashscreen(textures, font);
    while(playerNum >= 2 && playerNum <= 4)
    {
    winner = -1;
    elapsedTicks = 0;

    besucher = std::make_shared<std::vector<Besucher>>();

    spieler = std::make_shared<std::vector<Spieler>>();
    switch(playerNum)
    {
    case 4:
        spieler->push_back(Spieler(25, PLAYER_COLOR[playerNum - 4], sf::Vector2f(0 + 50, WINDOW_HEIGHT - 50), sf::Vector2f( 1, -1), Spieler::Controls::HJKL, besucher, font, playerNum - 4));
    case 3:
        spieler->push_back(Spieler(25, PLAYER_COLOR[playerNum - 3], sf::Vector2f(WINDOW_WIDTH - 50, 0 + 50),  sf::Vector2f(-1,  1), Spieler::Controls::ARROW_KEYS, besucher, font, playerNum - 3));
    case 2:
        spieler->push_back(Spieler(25, PLAYER_COLOR[playerNum - 2], sf::Vector2f(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50), sf::Vector2f(-1, -1), Spieler::Controls::KEYPAD, besucher, font, playerNum - 2));
    case 1:
        spieler->push_back(Spieler(25, PLAYER_COLOR[playerNum - 1], sf::Vector2f(0 + 50, 0 + 50), sf::Vector2f( 1,  1), Spieler::Controls::WASD, besucher, font, playerNum - 1));
        break;
    }

    sf::Color colorBuffer = sf::Color::White;
    for (int i = 0; i < MAX_BESUCHER; ++i) {
     //   switch( i % 3) {
       //     case 0 : colorBuffer = sf::Color::Blue; break;
         //   case 1 : colorBuffer = sf::Color::Green; break;
           // case 2 : colorBuffer = sf::Color::Red; break;
 //       }
        std::vector<float> fandom;
        for(int i = 0; i < playerNum; i++)
            fandom.push_back(gaussFandom(unrealEngine));
        besucher-> push_back(Besucher(sf::Vector2f(rand() % WINDOW_WIDTH - 100, rand() % WINDOW_HEIGHT - 100), 20,
                                     colorBuffer, randVec(BESCUHER_SPEED), gaussCharisma(unrealEngine), rand() % 10 + 1, fandom, textures));
    }

    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GameJam");

    sf::Text tm_show;
    tm_show.setFont(font);
    tm_show.setFillColor(sf::Color::Black);
    tm_show.setCharacterSize(64);
    char tm_chr[16];

    sf::Clock clock = sf::Clock();
    Events eventHandler = Events(window, spieler, besucher);
    while (window->isOpen()) {
        eventHandler.handleEvents(winner);
        if(elapsedTicks < TICKS_PER_GAME)
        {
            sf::Time t = clock.getElapsedTime();
            int elapsed = t.asMilliseconds();
            if (elapsed > MS_PER_TICK) {
                clock.restart();
                int ticks = floor((elapsed) / MS_PER_TICK);
                for(size_t i = 0; i < spieler->size(); i++){
                    (*spieler)[i].update(ticks);
                }
                for (size_t i = 0; i < MAX_BESUCHER; ++i) {
                    (*besucher)[i].update(ticks, spieler);
                }
                besucherCollision(besucher);
                elapsedTicks += ticks;
            }
        }
        else if(winner < 0)
        {
            score = (int*)calloc(playerNum, sizeof(int));//init 0
            for(size_t i = 0; i < besucher->size(); i++)
            {
                score[ (*besucher)[i].whichIsTheMaxFandom() ] ++;
            }
            int plID = 0;
            int hs = 0;
            for(int i = 0; i < playerNum; i++) {
                if (hs < score[i]) {
                    plID = i;
                    hs = score[i];
                }
            }
            winner = plID;

        }
        //std::cerr << elapsedTicks << std::endl;
        window->clear(cBACKGROUND);

        for (int i = 0; i < MAX_BESUCHER; ++i) {
            (*besucher)[i].draw(window);
        }
        for (size_t i = 0; i < spieler-> size(); ++i) {
            (*spieler)[i].draw(window);
        }

        sprintf(tm_chr, "%i", TICKS_PER_GAME - elapsedTicks);
        tm_show.setString(tm_chr);
        tm_show.setCharacterSize(64);
        tm_show.setPosition((WINDOW_WIDTH - tm_show.getGlobalBounds().width) / 2.0, 10.0f);
        window->draw(tm_show);

        if(elapsedTicks >= TICKS_PER_GAME && winner >= 0)
        {

        #define RECT_HEIGHT 100
        #define RECT_WIDTH  200
            sf::Text text[5];
            char pts[4][8];
            sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(RECT_WIDTH, RECT_HEIGHT));
            rect.setFillColor(sf::Color::Black);
            std::vector<sf::Vector2f> recPos;
            switch(playerNum)
            {
            case 4:
                recPos.push_back(sf::Vector2f(0 + 50, WINDOW_HEIGHT - 50 - RECT_HEIGHT));
            case 3:
                recPos.push_back(sf::Vector2f(WINDOW_WIDTH - 50 - RECT_WIDTH, 0 + 50));
            case 2:
                recPos.push_back(sf::Vector2f(WINDOW_WIDTH - 50 - RECT_WIDTH, WINDOW_HEIGHT - 50 - RECT_HEIGHT));
            case 1:
                recPos.push_back(sf::Vector2f(0 + 50, 0 + 50));
                break;
            }
            for (int i = 0; i < playerNum; ++i) {
                sprintf(pts[i], "%i", score[i]);
                text[i].setFont(font);
                text[i].setCharacterSize(64);
                text[i].setFillColor(PLAYER_COLOR[i]);
                text[i].setString(pts[i]);
                sf::Vector2f vec;
                rect.setPosition(recPos[i]);
                vec = sf::Vector2f((RECT_WIDTH - text[i].getGlobalBounds().width) / 2.0 , (RECT_HEIGHT - text[i].getGlobalBounds().height) / 5.0);
                text[i].setPosition(rect.getPosition() + vec);


                window->draw(rect);
                window->draw(text[i]);
            }

            char str[256];
             sprintf(str, "YOU WIN!!\n\t%i", score[winner]);
            text[4].setString(str);
            text[4].setFillColor(PLAYER_COLOR[winner]);
            text[4].setFont(font);
            text[4].setCharacterSize(80);
            text[4].setPosition(WINDOW_HWIDTH - text[4].getGlobalBounds().height / 2, WINDOW_HHEIGHT - text[4].getGlobalBounds().width / 2);
            sf::RectangleShape frame = sf::RectangleShape(sf::Vector2f(text[4].getGlobalBounds().width + 20.f, text[4].getGlobalBounds().height + 20.f));
            frame.setPosition(text[4].getGlobalBounds().left - 10.f, text[4].getGlobalBounds().top - 10);
            frame.setOutlineThickness(8);
            frame.setOutlineColor(sf::Color::Yellow);
            frame.setFillColor(sf::Color::Black);
            window->draw(frame);
            window->draw(text[4]);
        }
        window->display();
    }
    //free(score);
    std::cerr << "Start free" << std::endl;
    besucher.reset();
    spieler.reset();
    std::cerr << "Free all" << std::endl;
    playerNum = splashscreen(textures, font);
    }
}
