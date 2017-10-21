#include "Besucher.h"

Besucher::Besucher(sf::Vector2f pos, int radius, sf::Color color, sf::Vector2f mov, int charisma, int lambda, std::vector<float> fandom)
{
    mFandom = fandom;
    this->color = color;
    position = pos;
    movement = mov;
    this->radius = radius;
    interaktionCooldown = 0;
    mSpeed = sqrt(mov.x * mov.x + mov.y * mov.y);
    mCharisma = charisma;
    mWavelength = lambda;
}

void Besucher::update(int ellapsedTicks)
{
    if(interaktionCooldown < ellapsedTicks)
    {
        interaktionCooldown = 0;
        color = sf::Color::White;
    }
    else
        interaktionCooldown -= ellapsedTicks;

    position += movement * (1.0f * ellapsedTicks);

    if(position.x > WINDOW_WIDTH - radius * 2)
        movement = rotateVec(sf::Vector2f(-mSpeed, 0), rand() % 160 - 80);
    else if (position.x < 0 )
        movement = rotateVec(sf::Vector2f( mSpeed, 0), rand() % 160 - 80);
    if(position.y > WINDOW_HEIGHT - radius * 2)
        movement = rotateVec(sf::Vector2f(0, -mSpeed), rand() % 160 - 80);
    else if(position.y < 0)
        movement = rotateVec(sf::Vector2f(0,  mSpeed), rand() % 160 - 80);

}
void Besucher::draw(std::shared_ptr<sf::RenderWindow> win)
{
    sf::CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setPosition(position.x, position.y);
    win->draw(shape);
}

bool Besucher::collided(Besucher *besucher)
{
    sf::Vector2f delta = this->position - besucher->position;
    if(delta.x * delta.x + delta.y * delta.y <= (this->radius +  besucher->radius) * (this->radius + besucher->radius))
        return true;
    else
        return false;
}

void besucherCollision(std::shared_ptr<std::vector<Besucher>> besucher)
{
    for(size_t i = 0 ; i < besucher->size(); i++)
    {
        if((*besucher)[i].canInteract())
        {
            for(size_t j = i + 1; j < besucher->size(); j++)
            {
                if((*besucher)[j].canInteract())
                {
                    if((*besucher)[i].collided(&((*besucher)[j])) )
                    {
                        int r = (*besucher)[i].color.r + (*besucher)[j].color.r;
                        int g = (*besucher)[i].color.g + (*besucher)[j].color.g;
                        int b = (*besucher)[i].color.b + (*besucher)[j].color.b;
                        r /= 2;
                        g /= 2;
                        b /= 2;
                        (*besucher)[i].color = sf::Color(r, g, b);
                        (*besucher)[j].color = sf::Color(r, g, b);

                        (*besucher)[i].interaktionCooldown = IMMUNITY;
                        (*besucher)[j].interaktionCooldown = IMMUNITY;

                        // Apprallen mit Zufallswinkel
                        sf::Vector2f vecBuffer = (*besucher)[i].movement;
                        (*besucher)[i].movement = rotateVec((*besucher)[j].movement, rand() % REFLECTION_ANGLE - REFLECTION_ANGLE / 2);
                        (*besucher)[j].movement = rotateVec(vecBuffer, rand() % REFLECTION_ANGLE - REFLECTION_ANGLE / 2);


                    }
                }
            }
        }
    }
}

float Besucher::maxFandom()
{

}

float Besucher::standhaftigkeit()
{
    return mCharisma;
}

bool Besucher::interactsWith(Besucher *besucher)
{
    int dCharisma = abs(this-> mCharisma - besucher-> mCharisma);
    int dWaveLen  = getWaveDifference(this-> mWavelength, besucher-> mWavelength);
    vecf dFandom  = *vec_Sub(&this-> mFandom, &besucher-> mFandom);
}
