#ifndef BESUCHER_H
#define BESUCHER_H 0

#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Main.h"
#include "Spieler.h"
class Spieler;
class Besucher
{
public:

    sf::Color color;
    int interaktionCooldown;
    sf::Vector2f movement;
    sf::Vector2f position;
    std::vector<float> mFandom;
    int mAggressionLvl;
    int aggro;
    int mood;

    Besucher(sf::Vector2f pos, int radius, sf::Color color, sf::Vector2f mov, int charisma, int lambda, std::vector<float> fandom, std::shared_ptr<std::vector<sf::Texture>> textures);

    static int getWaveDifference(int wl1, int wl2)
    {
        if (wl1 > wl2)
            return ( wl1 - wl2 < wl2 + 10 - wl1 ? wl1 - wl2 : wl2 + 10 - wl1 );
        else
            return ( wl2 - wl1 < wl1 + 10 - wl2 ? wl2 - wl1 : wl1 + 10 - wl2 );
    }

    void update(int ellapsedTick, std::shared_ptr<std::vector<Spieler>> spieler);
    void draw(std::shared_ptr<sf::RenderWindow> win);
    bool canInteract(){return (interaktionCooldown <= 0);}
    bool collided(Besucher *besucher);

    float maxFandom();
    int  whichIsTheMaxFandom();
    float standhaftigkeit();
    bool converge(Besucher *besucher);
    void increaseAggression(int playerId);
    void addStun(int stun);
    void addMerch(size_t units);
    void giveMerch(Besucher *besucher);
private:
    std::shared_ptr<std::vector<sf::Texture>> mTextures;
    int mStun;
    int mRadius;
    int mSpeed;


    int mCharisma; // range 1 to 10

    int mWavelength; //range 1 to 10
    int mNMerch;

    bool mEvil;
};

void besucherCollision(std::shared_ptr<std::vector<Besucher>> besucher);

#endif /* !BESUCHER_H */
