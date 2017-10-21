#ifndef SPIELER_H
#define SPIELER_H 0

#include "Main.h"
#include "Besucher.h"

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Spieler
{
public:
    enum Controls{WASD, HJKL, ARROW_KEYS, KEYPAD};
    Spieler(int radius, sf::Color colour, sf::Vector2f pos, Controls controler, std::shared_ptr<std::vector<Besucher>> besucher);
    void draw(std::shared_ptr<sf::RenderWindow> win);
    void megaphone();
    void move(bool forwards, int steps);
    void turn(int deg);
    void update(int elapsedTicks);

private:
    std::shared_ptr<std::vector<Besucher>> pBesucher;
    int mRadius;
    sf::Color mColour, mConeColour;
    sf::Vector2f mPosition, mDirection;
    sf::Keyboard::Key up, down, left, right, shout;
    Controls mControler;

};

#endif /* !SPIELER_H */
