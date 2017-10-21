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
    srand(time(NULL));
    const sf::Color cBACKGROUND(0x00, 0x00, 0x00);//);
    std::default_random_engine unrealEngine;
    std::normal_distribution<double> gaussCharisma( 4, 1.2);
    std::normal_distribution<double> gaussFandom(0.2, 0.2);

    long playerNum = 3;


    std::shared_ptr<std::vector<Besucher>> besucher;
    besucher = std::make_shared<std::vector<Besucher>>();

    std::shared_ptr<std::vector<Spieler>> spieler;
    spieler = std::make_shared<std::vector<Spieler>>();
    spieler-> push_back(Spieler(25, sf::Color(0xFF, 0x00, 0x00), sf::Vector2f(WINDOW_HWIDTH, WINDOW_HHEIGHT), Spieler::Controls::WASD, besucher));
    spieler-> push_back(Spieler(25, sf::Color(0x00, 0x00, 0xFF), sf::Vector2f(WINDOW_HWIDTH, WINDOW_HHEIGHT), Spieler::Controls::KEYPAD, besucher));
    spieler-> push_back(Spieler(25, sf::Color(0x00, 0xFF, 0x00), sf::Vector2f(WINDOW_HWIDTH, WINDOW_HHEIGHT), Spieler::Controls::ARROW_KEYS, besucher));

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
                                     colorBuffer, randVec(5), gaussCharisma(unrealEngine), rand() % 10 + 1, fandom));
    }

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GameJam");

    sf::Font font;
    if (!font.loadFromFile("data/Oxygen-Sans.ttf")) {
        std::cerr << "Couldn‘t load font from ‘data/Oxygen-Sans.ttf’" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Text text("", font, 36);
    text.setFillColor(sf::Color::Cyan);
    text.setOutlineColor(sf::Color::Red);

    sf::Clock clock = sf::Clock();
    Events eventHandler = Events(window, spieler, besucher);
    while (window->isOpen()) {
        eventHandler.handleEvents();

        sf::Time t = clock.getElapsedTime();
        int elapsed = t.asMilliseconds();
        if (elapsed > MS_PER_TICK) {
            clock.restart();
            int ticks = floor((elapsed) / MS_PER_TICK);
            for(int i = 0; i < spieler->size(); i++){
                (*spieler)[i].update(ticks);
            }
            for (int i = 0; i < MAX_BESUCHER; ++i) {
                (*besucher)[i].update(ticks);
            }
            besucherCollision(besucher);
        }

        window->clear(cBACKGROUND);

        window->draw(text);

        for (int i = 0; i < MAX_BESUCHER; ++i) {
            (*besucher)[i].draw(window);
        }
        for (int i = 0; i < spieler-> size(); ++i) {
            (*spieler)[i].draw(window);
        }

        window->display();
    }
}
