#include "Besucher.h"

Besucher::Besucher(sf::Vector2i pos, int size, sf::Color color, sf::Vector2i mov)
{
    this.color = color;
    position = pos;
    movement = mov;
    this.size = size;
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
    sf::CircleShape shape(size);
    shape.setColor(color);
    shape.setCenter(posiion);
    win.draw(shape);
}