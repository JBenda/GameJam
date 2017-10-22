#ifndef SPLASH_H
#define SPLASH_H 0

#include "Main.h"
#include "Besucher.h"
#include "README.h"

int splashscreen(std::shared_ptr<std::vector<sf::Texture>> textures, sf::Font font);

#define BUBBLE_SIZE 60

#define NUM_BUBBLES  25

#define SPLASH_HEIGHT 550

#define SPLASH_WIDTH 450

const sf::Color BUBBLE_COLOR[4] = {sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, sf::Color::Yellow};

const sf::Color SELECTED_COLOR[4] = {sf::Color(0x00, 0x80, 0x00), sf::Color(0x00, 0x00, 0xA0), sf::Color(0x80, 0x00, 0x70), sf::Color(0xA0, 0xA0, 0x00)};

extern int splashscreen();

#endif // SPLASH_H
