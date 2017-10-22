#ifndef MAIN_H
#define MAIN_H 0

#include <random>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <malloc.h>
#include <stdlib.h>

typedef std::vector<float> vecf;

const sf::Color README_COLOR[2] = {sf::Color(sf::Color::Cyan), sf::Color(0x00, 0x80, 0x80)};
const sf::Color CALL_COLOR[2] = {sf::Color(0xF0, 0xF0, 0x00, 0x80), sf::Color(0x88, 0x88, 0x00, 0x80)};
const sf::Color PLAYER_COLOR[4] = {sf::Color(0xFF, 0x00, 0x00), sf::Color(0x00, 0xFF, 0x00), sf::Color(0x00, 0x00, 0xFF), sf::Color(0xFF, 0xFF, 0x00)};
#include "Utils.h"
#include "Splash.h"

#define AGGRESSION_VISIBLITY 70

enum TEXTURES{AGGRO, BAD_REACTION, GOOD_REACTION, MERCHANT};

#define WINDOW_WIDTH       1920
#define WINDOW_HEIGHT      1080

#define WINDOW_HWIDTH  (WINDOW_WIDTH / 2.0f)
#define WINDOW_HHEIGHT (WINDOW_HEIGHT / 2.0f)

#define MAX_BESUCHER        500

#define STARTING_MERCHANDISE  8
#define MERCH_HANDOUT_DIST  200
#define MERCH_PER_BOX        18
#define MERCH_INC           .3f

#define  BESCUHER_SPEED       4

#define MAX_CHARISMA         10
#define MAX_DLAMBDA           5

#define MS_PER_TICK          20

#define STUN_DURATION        50
#define CALL_DURATION         8

#define IMMUNITY              8

#define REFLECTION_ANGLE    100

#define CONE_ANGLE        25.0f
#define MEGAPHONE_RANGE  350.0f
#define VELOCITY           5.0f
#define AGGRO_FAC          1.0f

#define TICKS_PER_GAME     1200

#define ROTATION_PER_TICK    10

#define OBVIOUS_FANDOM     0.8f
#endif /* MAIN_H */
