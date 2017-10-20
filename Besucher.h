#ifndef BESUCHER
#define BESUCHER

#include <stdlib>
#include <vector>

class Besucher
{
public:
    static getWaveDifference(int wL1, int wL2)
    {
        if(wL1 > wL2)
        {
            return ( wL1 - wl2 < wL2 + 10 - wL1 ? wl1 - wl2 : wl2 + 10 - wL1 );
        }
        else
            return ( wL2 - wl1 < wL1 + 10 - wL2 ? wl2 - wl1 : wl1 + 10 - wL2 );
    }
private:
    std::Vector<int> position[2];
    std::Vector<float> fandom;
    int wellenLaenge; //value 1 - 10
    int ammountMerch;
    float agressionLvl;
    bool eviel;
}

#endif