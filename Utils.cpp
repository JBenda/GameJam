#include "utils.h"

sf::Vector2f rotateVec(sf::Vector2f vec, int degree)
{
    sf::Vector2f result(0,0);
    float rad = degree / 180.0 * M_PI;
    result.x = vec.x * cos(rad) - vec.y * sin(rad);
    result.y = vec.x * sin(rad) + vec.y * cos(rad);
    return result;
}

sf::Vector2f randVec(int len)
{
    sf::Vector2f r = sf::Vector2f(rand() % 2 * len - len, 0);
    r.y = sqrt(len * len - r.x * r.x);
    r.y *= rand() % 2 == 0 ? -1 : 1;
    return r;
}
