#include "print.h"

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::Drawable &initials)
{
    window.clear(sf::Color::White);
    window.draw(initials);
    window.display();
}