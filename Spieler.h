#ifndef SPIELER_H
#define SPIELER_H 0

#include "Main.h"
#include "Besucher.h"

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
class Besucher;
class Spieler
{
public:
    enum Controls{WASD, HJKL, ARROW_KEYS, KEYPAD, JOYSTICK};
    Spieler(int radius, sf::Color colour, sf::Vector2f pos, sf::Vector2f dir, Controls controler, std::shared_ptr<std::vector<Besucher>> besucher, sf::Font font, size_t id);
    void draw(std::shared_ptr<sf::RenderWindow> win);
    void megaphone();
    void move(bool forwards, int steps);
    void turn(int deg);
    void update(int elapsedTicks);
    sf::Vector2f mPosition, mDirection;
    void addStun(int stun);
    void handoutMerch();
    int mRadius;
private:
    int mCall;
    bool merchLocked;
    int mStun;
    size_t mID;
    size_t mNMerch;
    sf::Font mFont;
    std::shared_ptr<std::vector<Besucher>> pBesucher;

    sf::Color mColour, mConeColour;

    sf::Keyboard::Key up, down, left, right, shout, merch;
    Controls mControler;

};

#endif /* !SPIELER_H */
