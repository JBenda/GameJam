#include "Splash.h"
#include "README.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <string>

int splashscreen(std::shared_ptr<std::vector<sf::Texture>> textures, sf::Font font)
{
    sf::Texture readMeTex;
    sf::Vector2i readMePos(30, SPLASH_WIDTH - 30);
    bool readmeSelected = false;
    if(! readMeTex.loadFromFile("data/README.png"))
        std::cerr << "Failed to load Textuer from data/README.png" << std::endl;

    int selectedBubble = -1;
    char *TEXT_OUT[6] = {"2", "3", "4", "Cancel", "Choose Player Number", "BUBBLES"};
    std::shared_ptr<sf::RenderWindow> win = std::make_shared<sf::RenderWindow>(sf::VideoMode(SPLASH_WIDTH, SPLASH_HEIGHT), TEXT_OUT[5]);
    int result = -1;

    std::vector<Besucher> besucher = std::vector<Besucher>();
    std::vector<float> fandom = std::vector<float>();

    std::vector<sf::CircleShape> bubbles = std::vector<sf::CircleShape>(4);
    std::vector<sf::Text> text = std::vector<sf::Text>(6);
    //std::cerr << "Init 1. Part" << std::endl;
    sf::Vector2f position;
    for(int i = 0; i < 4; i++)
    {
        bool correct = false;
        while(!correct)
        {
            position.x = 15.f + rand() % (SPLASH_WIDTH - 30 - BUBBLE_SIZE*2);
            position.y = 100.f + rand() % (SPLASH_HEIGHT - 215 - BUBBLE_SIZE * 2);
            correct = true;
            for(int j = i - 1; j >= 0; j --)
            {
                if(vecLen(position - bubbles[j].getPosition()) < BUBBLE_SIZE * 2)
                {
                    correct = false;
                    break;
                }
            }
        }

        bubbles[i] = sf::CircleShape(BUBBLE_SIZE);
        bubbles[i].setPosition( position);
        bubbles[i].setFillColor(BUBBLE_COLOR[i]);

        text[i].setFont(font);
        text[i].setCharacterSize(i != 3 ? 50 : 30);
        text[i].setFillColor(sf::Color::Black);
        text[i].setString(TEXT_OUT[i]);
        text[i].setPosition(bubbles[i].getPosition().x + BUBBLE_SIZE - text[i].getGlobalBounds().width / 2,
                            bubbles[i].getPosition().y + BUBBLE_SIZE - text[i].getGlobalBounds().height);
    }
    for (int i = 0; i < NUM_BUBBLES; ++i) {
        bool correct = false;
        while(!correct)
        {
            correct = true;
            position.x = 20 + rand() % (SPLASH_WIDTH - 40);
            position.y = 20 + rand() % (SPLASH_HEIGHT - 40);
            for(int j = 0; j < 4; j++)
            {
                if(     vecLen(bubbles[j].getPosition() + sf::Vector2f(BUBBLE_SIZE, BUBBLE_SIZE) - position - sf::Vector2f(20.f, 20.f))
                   <    BUBBLE_SIZE + 30)
                {
                    correct = false;
                    //break;
                }
            }
            for(int j = i - 1; j >= 0; j--)
            {
                if(vecLen(position - besucher[j].position ) < 50 )
                {
                    correct = false;
                    //break;
                }
            }
        }
        besucher.push_back(Besucher(sf::Vector2f(rand() % SPLASH_WIDTH - 25, rand() % SPLASH_HEIGHT - 25), 20,
                               sf::Color(rand() % 256, rand() % 256, rand() % 256), sf::Vector2f(0.f, 0.f), 0, 0, fandom, textures));
        besucher[i].mood = rand() % 5 - 1;
    }
    text[4].setFont(font);
    text[4].setCharacterSize(40);
    text[4].setFillColor(sf::Color::Green);
    text[4].setString(TEXT_OUT[4]);
    text[4].setPosition(20, SPLASH_WIDTH / 2 - text[4].getGlobalBounds().width/2);
    //std::cerr << "Finished Build" << std::endl;
    while (win->isOpen()) {
        sf::Event event;
        while (win->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    win->close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(readmeSelected && event.mouseButton.button == sf::Mouse::Left)
                        showReadMe();
                    if(selectedBubble >= 0 && event.mouseButton.button ==  sf::Mouse::Left)
                    {
                        switch(selectedBubble)
                        {
                        case 0: result = 2; break;
                        case 1: result = 3; break;
                        case 2: result = 4; break;
                        case 3: result = -1; break;
                        }
                        win->close();
                    }
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        win->close();
                    break;
                default: break;
            }
        }
        bool unselect = true;
        for(int i = 0; i < 4; i ++)
        {
            if(vecLen(sf::Mouse::getPosition(*win) - sf::Vector2i( floor(bubbles[i].getPosition().x) + BUBBLE_SIZE, floor(bubbles[i].getPosition().y) + BUBBLE_SIZE )) < BUBBLE_SIZE )
            {
                if(i != selectedBubble)
                {
                    bubbles[selectedBubble].setFillColor(BUBBLE_COLOR[selectedBubble]);
                    text[selectedBubble].setFillColor(sf::Color::Black);
                    selectedBubble = i;
                    bubbles[i].setFillColor(SELECTED_COLOR[i]);
                    text[i].setFillColor(sf::Color::White);
                }
                unselect = false;
                break;
            }
        }
        if(unselect)
        {
            bubbles[selectedBubble].setFillColor(BUBBLE_COLOR[selectedBubble]);
            text[selectedBubble].setFillColor(sf::Color::Black);
            selectedBubble = -1;
        }

        if(vecLen(sf::Mouse::getPosition(*win) - readMePos + sf::Vector2i(12, 12)) < 25)
        {
            readmeSelected = true;
        }
        else
            readmeSelected = false;
        //std::cerr << "Start Draw" << std::endl;
        win->clear(sf::Color::Black);
        //std::cerr << "background finished" << std:: endl;
        sf::CircleShape readme(25);
        readme.setPosition(readMePos.x, readMePos.y);
        readme.setFillColor( readmeSelected ? README_COLOR[0] : README_COLOR[1] );
        win->draw(readme);
        readme.setTexture(&readMeTex);
        win->draw(readme);

        for(int i = 0; i < NUM_BUBBLES; i++)
        {
            besucher[i].draw(win);
        }
        //std::cerr << "start draw part 2" << std::endl;
        for(int i = 0; i < 4; i++)
        {
            win->draw(bubbles[i]);
            win->draw(text[i]);
        }

        win->draw(text[4]);

        win->display();
        //std::cerr << "Finehsd DRaw" << std::endl;
    }
    return result;
}
