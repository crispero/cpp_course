#include "print.h"
#include "initials.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Ball",
        sf::Style::Default, settings);

    sf::Clock clock;

    Initials initials;
    initials.initBall();
    initials.initText();

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window);
        initials.update(deltaTime);
        redrawFrame(window, initials);
    }
}