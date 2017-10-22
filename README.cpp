#include "README.h"

#define RM_W 800
#define RM_H RM_W

void showReadMe()
{
    sf::Texture texture;
    if (!texture.loadFromFile("data/readme.png")) {
        std::cerr << "Couldn’t load readme..." << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(RM_W, RM_H), "ReadMe");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    window.close();
                    break;
                default: break;
            }
        }

        sf::RectangleShape rsh(sf::Vector2f(RM_W, RM_H));
        rsh.setPosition(0,0);
        rsh.setTexture(&texture, true);

        window.clear(sf::Color::White);
        window.draw(rsh);
        window.display();
    }
}
