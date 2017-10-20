#include "Besucher.h"

Besucher::Besucher(sf::Vector2i pos, int radius, sf::Color color, sf::Vector2i mov)
{
    this->color = color;
    position = pos;
    movement = mov;
    this->radius = radius;
    interaktionCooldown = 0;
}

void Besucher::update(int ellapsedTicks)
{
    if(interaktionCooldown < ellapsedTicks)
        interaktionCooldown = 0;
    else
        interaktionCooldown -= ellapsedTicks;

    position += movement * ellapsedTicks;

    if(position.x > WINDOW_WIDTH - radius * 2 || position.x < 0 )
        movement.x = - movement.x;
    if(position.y > WINDOW_HEIGHT - radius * 2 || position.y < 0)
        movement.y = - movement.y;

}
void Besucher::draw(std::shared_ptr<sf::RenderWindow> win)
{
    sf::CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setPosition(position.x, position.y);
    win->draw(shape);
}

bool Besucher::colited(Besucher *besucher)
{
    sf::Vector2i delta = this->position - besucher->position;
    if(delta.x * delta.x + delta.y * delta.y <= (this->radius +  besucher->radius) * (this->radius + besucher->radius))
        return true;
    else
        return false;
}

void besucherCollision(std::shared_ptr<std::vector<Besucher>> besucher)
{
    for(int i = 0 ; i < besucher->size(); i++)
    {
        if((*besucher)[i].canInteract())
        {
            for(int j = i + 1; j < besucher->size(); j++)
            {
                if((*besucher)[j].canInteract())
                {
                    if((*besucher)[i].colited(&((*besucher)[j])) )
                    {
                        std::cout << "Hej!" << std::endl;
                        sf::Color colorBuffer = (*besucher)[i].color;
                        (*besucher)[i].color = (*besucher)[j].color;
                        (*besucher)[j].color = colorBuffer;
                        (*besucher)[i].interaktionCooldown = IMMUNITY;
                        (*besucher)[j].interaktionCooldown = IMMUNITY;
                    }
                }
            }
        }
    }
}
