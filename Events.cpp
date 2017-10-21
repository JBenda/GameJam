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

void Events::handleEvents()
{
    sf::Event event;
    while (mWindow->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                mWindow->close();
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        mWindow->close();
                        break;
                    case sf::Keyboard::W:
                        (*mSpieler)[0].move(mWindow,  true);
                        break;
                    case sf::Keyboard::A:
                        (*mSpieler)[0].turn(-5, mWindow);
                        break;
                    case sf::Keyboard::S:
                        (*mSpieler)[0].move(mWindow, false);
                        break;
                    case sf::Keyboard::D:
                        (*mSpieler)[0].turn( 5, mWindow);
                        break;
                    case sf::Keyboard::Space:
                        (*mSpieler)[0].shout(mBesucher);
                        break;
                    default: break;
                }
                break;

            default: break;
        }
    }
}
