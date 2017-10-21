#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Main.h"

extern float DegToRad(float deg);

sf::Vector2f rotateVec(sf::Vector2f vec, int degree);

sf::Vector2f randVec(int len);

float vecLen(sf::Vector2f);
float crossProd(sf::Vector2f vecA, sf::Vector2f vecB);
float dotProd(sf::Vector2f vecA, sf::Vector2f vecB);

size_t vec_EquDimens(vecf *vecA, vecf *vecB);
vecf* vec_Sub(vecf *vecA, vecf *vecB);
vecf* vec_Add(vecf *vecA, vecf *vecB);
vecf* vec_Mul(vecf *vecA, float fac);

#endif // ! UTILS_H
