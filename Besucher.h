#ifndef BESUCHER_H
#define BESUCHER_H

#include <cstdlib>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Main.h"



void besucherColision(std::vector<Besucher> besucher)
{
    for(int i = 0 ; i < besucher.length; i++)
    {
        if(besucher[i].canInteract())
        {
            for(int j = i + 1; j < besucher.length; j++)
            {
                if(besucher[j].canInteract())
                {
                    if(besucher[i].colited(&besucher[j]) )
                    {
                        sf::Color colorBuffer = besucher[i].color;
                        besucher[i].color = besucher[j].color;
                        besucher[j].color = colorBuffer;
                    }
                }
            }
        }
    }
}

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
    void update(int ellapsedTick);
    void draw(std::shared_ptr<sf::RenderWindow> win);
    bool canInteract(){return (interaktionCooldown <= 0);}
    bool colited(Besucher *besucher);

    sf::Color color;
private:
    int size;
    
    sf::Vector2i position;
    sf::Vector2i movement;
    std::vector<float> fandom;
    int wavelength; //value 1 - 10
    int ammountMerch;
    float aggressionLvl;
    bool evil;
    int interaktionCooldown;
};

#endif /* !BESUCHER_H */
