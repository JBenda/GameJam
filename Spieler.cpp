#include "Spieler.h"

#define CONE_ANGLE 25

Spieler::Spieler(int radius, sf::Color colour, sf::Vector2f pos, Controls controler, std::shared_ptr<std::vector<Besucher>> besucher)
{
    pBesucher = besucher;
    mRadius = radius;
    mColour = colour;
    mPosition = pos;
    mDirection = sf::Vector2f(0, -200);
    mConeColour = sf::Color(0x80, 0x80, 0x80, 0x80);
    mControlern = controler;
    switch(mControler)
    {
        case ARROW_KEYS:
            up = sf::Keyboard::Key::Up;
            down = sf::Keyboard::Key::Down;
            left = sf::Keyboard::Key::Left;
            right = sf::Keyboard::Key::Right;
            shout = sf::Keyboard::Key::RShift;
          break;
        case WSAD:
            up = sf::Keyboard::Key::W;
            down = sf::Keyboard::Key::S;
            left = sf::Keyboard::Key::A;
            right = sf::Keyboard::Key::D;
            shout = sf::Keyboard::Key::Q;
          break;
    }
}

void Spieler::draw(std::shared_ptr<sf::RenderWindow> win)
{
    const sf::Vector2f halfRadius(mRadius / 2.0, mRadius / 2.0);

    sf::Vector2f leftSide  = mPosition + rotateVec(mDirection,  CONE_ANGLE);
    sf::Vector2f rightSide = mPosition + rotateVec(mDirection, -CONE_ANGLE);
    leftSide  += halfRadius;
    rightSide += halfRadius;

    sf::ConvexShape cv;
    cv.setPointCount(3);
    cv.setPoint(0, mPosition + halfRadius);
    cv.setPoint(1, rightSide);
    cv.setPoint(2, leftSide);
    cv.setFillColor(mConeColour);
    win-> draw(cv);

    sf::CircleShape shape = sf::CircleShape(mRadius);
    shape.setFillColor(mColour);
    shape.setPosition(mPosition.x - mRadius / 2, mPosition.y - mRadius / 2);
    win-> draw(shape);
}

void Spieler::shout()
{
    sf::Vector2f leftSide, rightSide;
    leftSide  = rotateVec(mDirection, -15);
    rightSide = rotateVec(mDirection,  15);

    sf::Vector2f v = sf::Vector2f();
    for (size_t i = 0; i < pBesucher-> size(); ++i) {
        sf::Vector2f b = leftSide - mPosition;
        sf::Vector2f c = rightSide - mPosition;
        sf::Vector2f p = (*pBesucher)[i].position - mPosition;
    }
}

void Spieler::move(bool forwards, int steps)
{
    mPosition += forwards ? mDirection * steps : -mDirection * steps;
}

void Spieler::turn(int deg)
{
    mDirection = rotateVec(mDirection, deg);
}

void update(int elapsedTicks)
{
    if( sf::Keyboard::isKeyPressed(up) )
        move(true, elapsedTicks);
    if( sf::Keyboard::isKeyPressed(down))
        move(false, elapsedTicks);
    if( sf::Keyboard::isKeyPressed(left))
        turn(ROATAION_PER_TICK);
    if( sf::Keyboard::isKeyPressed(right))
        turn(-ROATAION_PER_TICK);
    if( sf::Keyboard::isKeyPressed(shout))
        shout();
}