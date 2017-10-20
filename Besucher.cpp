#include "Besucher.h"

Besucher::Besucher(sf::Vector2i pos, int size, sf::Color color, sf::Vector2i mov)
{
    this->color = color;
    position = pos;
    movement = mov;
    this->size = size;
    interaktionCooldown = 0;
}

void Besucher::update(int ellapsedTicks)
{
    if(interaktionCooldown < ellapsedTicks)
        interaktionCooldown = 0;
    else
        interaktionCooldown -= ellapsedTicks;

    position += movement * ellapsedTicks;

    if(position.x > WINDOW_WIDTH || position.x < 0 )
        movement.x = - movement.x;
    if(position.y > WINDOW_HEIGHT || position.y < 0)
        movement.y = - movement.y;

}
void Besucher::draw(std::shared_ptr<sf::RenderWindow> win)
{
    sf::CircleShape shape(size);
    shape.setFillColor(color);
    shape.setPosition(position.x, position.y);
    win->draw(shape);
}
