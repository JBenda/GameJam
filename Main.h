#ifndef MAIN_H
#define MAIN_H 0

#include <random>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

typedef std::vector<float> vecf;

const sf::Color CALL_COLOR[2] = {sf::Color(0xF0, 0xF0, 0x00, 0x80), sf::Color(0x88, 0x88, 0x00, 0x80)};
const sf::Color PLAYER_COLOR[3] = {sf::Color(0xFF, 0x00, 0x00), sf::Color(0x00, 0xFF, 0x00), sf::Color(0x00, 0x00, 0xFF)};
#include "Utils.h"

#define AGGRESSION_VISIBLITY 70

enum TEXTURES{AGGRO, BAD_REACTION, GOOD_REACTION, MERCHANT};

#define WINDOW_WIDTH       1500
#define WINDOW_HEIGHT       900

#define WINDOW_HWIDTH  (WINDOW_WIDTH / 2.0f)
#define WINDOW_HHEIGHT (WINDOW_HEIGHT / 2.0f)

#define MAX_BESUCHER        128

#define STARTING_MERCHANDISE  3
#define MERCH_PER_BOX        12
#define MERCH_INC           .3f

#define MAX_CHARISMA         10
#define MAX_DLAMBDA           5

#define MS_PER_TICK          20

#define STUN_DURATION        50
#define CALL_DURATION         8

#define IMMUNITY              8

#define REFLECTION_ANGLE    100

#define CONE_ANGLE        25.0f
#define MEGAPHONE_RANGE  200.0f
#define VELOCITY           5.0f

#define TICKS_PER_GAME     1200

#define ROTATION_PER_TICK    10

#endif /* MAIN_H */
