#ifndef BESUCHER_H
#define BESUCHER_H

#include <cstdlib>
#include <vector>

#include <SFML/System/Vector2.hpp>

class Besucher
{
public:
    static int getWaveDifference(int wl1, int wl2)
    {
        if (wl1 > wl2)
            return ( wl1 - wl2 < wl2 + 10 - wl1 ? wl1 - wl2 : wl2 + 10 - wl1 );
        else
            return ( wl2 - wl1 < wl1 + 10 - wl2 ? wl2 - wl1 : wl1 + 10 - wl2 );
    }
private:
    sf::Vector2<int> position;
    std::vector<float> fandom;
    int wavelength; //value 1 - 10
    int ammountMerch;
    float aggressionLvl;
    bool eviel;
};

#endif /* !BESUCHER_H */
