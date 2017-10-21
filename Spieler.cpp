#include "Spieler.h"

Spieler::Spieler(int radius, sf::Color colour, sf::Vector2f pos)
{
    mRadius = radius;
    mColour = colour;
    mPosition = pos;
}

void Spieler::draw(std::shared_ptr<sf::RenderWindow> win)
{
    sf::CircleShape shape = sf::CircleShape(mRadius);
    shape.setFillColor(mColour);
    shape.setPosition(mPosition.x, mPosition.y);
}
