#ifndef SPIELER_H
#define SPIELER_H

#include "Main.h"

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Spieler
{
public:
    Spieler(int radius, sf::Color colour, sf::Vector2f pos);
    void draw(std::shared_ptr<sf::RenderWindow> win);

private:
    int mRadius;
    sf::Color mColour;
    sf::Vector2f mPosition;
};

#endif /* !SPIELER_H */
