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
    win-> draw(shape);
}

void Spieler::shout(std::shared_ptr<std::vector<Besucher>> besucher)
{
    sf::Vector2f leftSide, rightSide;
    leftSide  = rotateVec(mDirection, -15);
    rightSide = rotateVec(mDirection,  15);

    for (int i = 0; i < besucher-> size(); ++i) {
        sf::Vector2f v0 = (*besucher)[i].position;
    }
}

void Spieler::move(std::shared_ptr<sf::RenderWindow> win)
{
    mPosition += mDirection;
    draw(win);
}

void Spieler::turn(int deg, std::shared_ptr<sf::RenderWindow> win)
{
    mPosition = rotateVec(mPosition, deg);
    mPosition += mDirection / 2.0f;
    this-> move(win);
}
