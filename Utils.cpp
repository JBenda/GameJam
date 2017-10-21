#include "Utils.h"

float DegToRad(float deg)
{
    return deg / 180.0 * M_PI;
}

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

float vecLen(sf::Vector2f vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float crossProd(sf::Vector2f vecA, sf::Vector2f vecB)
{
    return (vecA.x * vecB.y) - (vecA.y * vecB.x);
}

float dotProd(sf::Vector2f vecA, sf::Vector2f vecB)
{
    return vecA.x * vecB.x + vecA.y * vecB.y;
}

/*********************************************************************************************
**  VECTOR UTILITY ROUTINES ******************************************************************
*********************************************************************************************/

size_t vec_EquDimens(vecf *vecA, vecf *vecB)
{
    size_t len = vecA-> size();
    return len == vecB-> size() ? len : 0;
}

vecf* vec_Sub(vecf *vecA, vecf *vecB)
{
    size_t len = vec_EquDimens(vecA, vecB);
    if (!len) return nullptr;

    vecf *result = new vecf();
    for (size_t i = 0; i < len; ++i) {
        (*result)[i] = (*vecA)[i] - (*vecB)[i];
    }
    return result;
}

vecf* vec_Add(vecf *vecA, vecf *vecB)
{
    size_t len = vec_EquDimens(vecA, vecB);
    if (!len) return nullptr;

    vecf *result = new vecf();
    for (size_t i = 0; i < len; ++i) {
        (*result)[i] = (*vecA)[i] + (*vecB)[i];
    }
    return result;
}

vecf* vec_Mul(vecf *vecA, float fac)
{
    size_t len = vecA-> size();

    vecf *result = new vecf();
    for (size_t i = 0; i < len; ++i) {
        (*result)[i] = (*vecA)[i] * fac;
    }
    return result;
}
