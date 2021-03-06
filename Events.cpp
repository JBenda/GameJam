#include "Main.h"
#include "Events.h"

Events::Events(std::shared_ptr<sf::RenderWindow>      window,
               std::shared_ptr<std::vector<Spieler>>  spieler,
               std::shared_ptr<std::vector<Besucher>> besucher)
{
    mWindow   = window;
    mSpieler  = spieler;
    mBesucher = besucher;
}

void Events::handleEvents(int winner)
{
    sf::Event event;
    while (mWindow->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                mWindow->close();
                break;
            case sf::Event::JoystickButtonPressed:
                if(winner >= 0 && event.joystickButton.button <= 3)
                    mWindow->close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Return:
                    if(winner < 0)
                        break;
                    case sf::Keyboard::Escape:
                        mWindow->close();
                        break;
                    default: break;
                }
                break;

            default: break;
        }
    }
}
