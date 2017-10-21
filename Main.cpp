#include "Main.h"
#include "Map.h"
#include "Besucher.h"
#include "Spieler.h"
#include "Events.h"

#include <iostream>
#include <memory>
#include <ctime>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    int winner = -1;
    int elapsedTicks = 0;
    std::shared_ptr<std::vector<sf::Texture>> textures;
    textures = std::make_shared<std::vector<sf::Texture>>(3);

    if( !(*textures)[TEXTURES::AGGRO].loadFromFile("data/skull.png"))
        std::cerr << "can't load Textture data/skull.png" << std::endl;
    if( !(*textures)[TEXTURES::BAD_REACTION].loadFromFile("data/biohazard.png"))
        std::cerr << "can't load Textture data/biohazard.png" << std::endl;
    if( !(*textures)[TEXTURES::GOOD_REACTION].loadFromFile("data/sun.png"))
        std::cerr << "can't load Textture data/sun.png" << std::endl;

    srand(time(NULL));
    const sf::Color cBACKGROUND(0x60, 0x60, 0x60);//);
    std::default_random_engine unrealEngine;
    std::normal_distribution<double> gaussCharisma( 4, 1.2);
    std::normal_distribution<double> gaussFandom(0.2, 0.2);

    long playerNum = 3;


    std::shared_ptr<std::vector<Besucher>> besucher;
    besucher = std::make_shared<std::vector<Besucher>>();

    std::shared_ptr<std::vector<Spieler>> spieler;
    spieler = std::make_shared<std::vector<Spieler>>();
    spieler-> push_back(Spieler(25, sf::Color(0xFF, 0x00, 0x00), sf::Vector2f(WINDOW_HWIDTH, WINDOW_HHEIGHT), Spieler::Controls::WASD, besucher, 0));
    spieler-> push_back(Spieler(25, sf::Color(0x00, 0x00, 0xFF), sf::Vector2f(WINDOW_HWIDTH, WINDOW_HHEIGHT), Spieler::Controls::KEYPAD, besucher, 1));
    spieler-> push_back(Spieler(25, sf::Color(0x00, 0xFF, 0x00), sf::Vector2f(WINDOW_HWIDTH, WINDOW_HHEIGHT), Spieler::Controls::ARROW_KEYS, besucher, 2));

    sf::Color colorBuffer = sf::Color::White;
    for (int i = 0; i < MAX_BESUCHER; ++i) {
     //   switch( i % 3) {
       //     case 0 : colorBuffer = sf::Color::Blue; break;
         //   case 1 : colorBuffer = sf::Color::Green; break;
           // case 2 : colorBuffer = sf::Color::Red; break;
 //       }
        std::vector<float> fandom;
        for(int i = 0; i < playerNum; i++)
            fandom.push_back(gaussFandom(unrealEngine));
        besucher-> push_back(Besucher(sf::Vector2f(rand() % WINDOW_WIDTH - 100, rand() % WINDOW_HEIGHT - 100), 20,
                                     colorBuffer, randVec(5), gaussCharisma(unrealEngine), rand() % 10 + 1, fandom, textures));
    }

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GameJam");

    sf::Font font;
    if (!font.loadFromFile("data/LinLibertine_R.otf")) {
        std::cerr << "Couldn‘t load font from ‘data/LinLibertine_R.otf’" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Clock clock = sf::Clock();
    Events eventHandler = Events(window, spieler, besucher);
    while (window->isOpen()) {
        eventHandler.handleEvents();
        if(elapsedTicks < TICKS_PER_GAME)
        {
            sf::Time t = clock.getElapsedTime();
            int elapsed = t.asMilliseconds();
            if (elapsed > MS_PER_TICK) {
                clock.restart();
                int ticks = floor((elapsed) / MS_PER_TICK);
                for(int i = 0; i < spieler->size(); i++){
                    (*spieler)[i].update(ticks);
                }
                for (int i = 0; i < MAX_BESUCHER; ++i) {
                    (*besucher)[i].update(ticks, spieler);
                }
                besucherCollision(besucher);
                elapsedTicks += ticks;
            }
        }
        else if(winner < 0)
        {
            int *score = (int*)calloc(playerNum, sizeof(int));//init 0
            for(size_t i = 0; i < besucher->size(); i++)
            {
                score[ (*besucher)[i].maxFandom() ] ++;
            }
            for(int i = 0; i < playerNum; i++)


        }
        window->clear(cBACKGROUND);

        for (int i = 0; i < MAX_BESUCHER; ++i) {
            (*besucher)[i].draw(window);
        }
        for (int i = 0; i < spieler-> size(); ++i) {
            (*spieler)[i].draw(window);
        }

        if(elapsedTicks >= TICKS_PER_GAME)
        {
            sf::Text text;
            text.setString("YOU WIN!!");
            text.setColor()
            text.setPosition()
            window->draw(text);
        }
        window->display();
    }
}
