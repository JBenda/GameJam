#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <SFML/Graphics.hpp>

sf::Vector2i rotateVec(sf::Vector2i vec, int degree)
{
    sf::Vector2i result(0,0);
    float rad = degree / 180 * PI;
    result.x = vec.x * cosf(rad) - vec.y * sinf(rad);
    result.y = vec.x * sinf(rad) + vec.y * sinf(rad);
}

#endif // ! UTILS_H