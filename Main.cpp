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
    const sf::Color cBACKGROUND(0x00, 0x00, 0x00);//0x80, 0x20, 0x14);

    std::vector<Besucher> besucher;//MAX_BESUCHER];
    besucher.push_back(Besucher(sf::Vector2i(120, 120), 20, sf::Color::Green, sf::Vector2i(5, 8)));

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
        std::cout << elapsed << std::endl;
        if (elapsed > MS_PER_TICK) {
            clock.restart();
            int ticks = floor((elapsed) / MS_PER_TICK);
            printf("%i\n", ticks);
            besucher[0].update(ticks);
        }

        window->clear(cBACKGROUND);

        window->draw(text);
        besucher[0].draw(window);

        window->display();
    }
}
