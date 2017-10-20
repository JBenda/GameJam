#ifndef BESUCHER_H
#define BESUCHER_H

#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Besucher
{
public:
    Besucher(sf::Vector2i pos, int siz, sf::Color color, sf::Vector2i mov);
    static int getWaveDifference(int wl1, int wl2)
    {
        if (wl1 > wl2)
            return ( wl1 - wl2 < wl2 + 10 - wl1 ? wl1 - wl2 : wl2 + 10 - wl1 );
        else
            return ( wl2 - wl1 < wl1 + 10 - wl2 ? wl2 - wl1 : wl1 + 10 - wl2 );
    }
    void update(int ellapsedTicks);
    void draw(sf::RenderWindow win);
private:
    int size;
    sf::Color color;
    sf::Vector2i position;
    sf::Vector2i movement;
    std::vector<float> fandom;
    int wavelength; //value 1 - 10
    int ammountMerch;
    float aggressionLvl;
    bool eviel;
    int interaktionCooldown;
};

#endif /* !BESUCHER_H */
