#include "Map.h"
#include "Besucher.h"
#include "Spieler.h"

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    const sf::Color cBACKGROUND(0x80, 0x20, 0x14);


    sf::RenderWindow window(sf::VideoMode(1024, 786), "GameJam");

    sf::Font font;
    if (!font.loadFromFile("data/Oxygen-Sans.ttf")) {
        std::cerr << "Couldn‘t load font from ‘data/Oxygen-Sans.ttf’" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Text text("Hello, world!", font, 36);
    text.setColor(sf::Color::Cyan);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                        default: break;
                    }
                    break;

                default: break;
            }
        }

        window.clear(cBACKGROUND);

        window.draw(text);

        window.display();
    }
}
