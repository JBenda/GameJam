#ifndef EVENTS_H
#define EVENTS_H 0

#include "Main.h"
#include "Spieler.h"
#include "Besucher.h"
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Events
{
public:
    Events(std::shared_ptr<sf::RenderWindow> win,
           std::shared_ptr<std::vector<Spieler>> spieler,
           std::shared_ptr<std::vector<Besucher>> besucher);
    void handleEvents();

private:
    std::shared_ptr<sf::RenderWindow> mWindow;
    std::shared_ptr<std::vector<Spieler>> mSpieler;
    std::shared_ptr<std::vector<Besucher>> mBesucher;
};

#endif /* !EVENTS_H */
