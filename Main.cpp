#include "Main.h"
#include "Map.h"
#include "Besucher.h"
#include "Spieler.h"

#include <iostream>
#include <memory>
#include <ctime>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    srand(time(NULL));
    const sf::Color cBACKGROUND(0x00, 0x00, 0x00);//0x80, 0x20, 0x14);
    std::default_random_engine unrealEngine;
    std::normal_distribution<double> gaussCharisma( 4, 1.2);
    std::normal_distribution<double> gaussFandom(0.2, 0.2);

    long playerNum = 3;

    std::shared_ptr<std::vector<Besucher>> besucher;//MAX_BESUCHER];
    besucher = std::make_shared<std::vector<Besucher>>();
    sf::Color colorBuffer;
    for (int i = 0; i < MAX_BESUCHER; ++i) {
        switch( i % 3)
        {
            case 0 : colorBuffer = sf::Color::Blue; break;
            case 1 : colorBuffer = sf::Color::Green; break;
            case 2 : colorBuffer = sf::Color::Red; break;
        }
        std::vector<float> fandom;
        for(int i = 0; i < playerNum; i++)
            fandom.push_back(gaussFandom(unrealEngine));
        besucher->push_back(Besucher(sf::Vector2f(rand() % 800 + 50, rand() % 600 + 40), 20, colorBuffer, randVec(5),
                                     gaussCharisma(unrealEngine), rand() % 10 + 1, fandom));
    }

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GameJam");

    sf::Font font;
    if (!font.loadFromFile("data/Oxygen-Sans.ttf")) {
        std::cerr << "Couldn‘t load font from ‘data/Oxygen-Sans.ttf’" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Text text("Hello, world!", font, 36);
    text.setFillColor(sf::Color::Cyan);
    text.setOutlineColor(sf::Color::Red);

    sf::Clock clock = sf::Clock();
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            window->close();
                        default: break;
                    }
                    break;

                default: break;
            }
        }

        sf::Time t = clock.getElapsedTime();
        int elapsed = t.asMilliseconds();
        if (elapsed > MS_PER_TICK) {
            clock.restart();
            int ticks = floor((elapsed) / MS_PER_TICK);
            besucherCollision(besucher);
            for (int i = 0; i < MAX_BESUCHER; ++i) {
                (*besucher)[i].update(ticks);
            }
        }

        window->clear(cBACKGROUND);

        window->draw(text);

        for (int i = 0; i < MAX_BESUCHER; ++i) {
            (*besucher)[i].draw(window);
        }

        window->display();
    }
}
