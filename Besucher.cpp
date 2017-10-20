#include "Besucher.h"

Besucher::Besucher(sf::Vector2i pos, int siz, sf::Color color, sf::Vector2i mov)
{
    myColor = color;
    position = pos;
    movement = mov;
    mySize = size;
    interaktionCooldown = 0;
}

void Besucher::update(int ellapsedTicks)
{
    if(interaktionCooldown < ellapsedTicks)
        interaktionCooldown = 0;
    else
        interaktionCooldown -= ellapsedTicks;

    position += movement * ellapsedTicks;

}
void Besucher::draw(sf::RenderWindow win)
{

}