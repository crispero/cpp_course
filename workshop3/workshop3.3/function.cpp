#include "function.h"

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void onMouseMove(sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
    sf::Vector2f distance = {WINDOW_WIDTH / 2 - mousePosition.x, WINDOW_HEIGHT / 2 - mousePosition.y};
    float length = std::sqrt(std::pow(distance.x, 2) + std::pow(distance.y, 2));
    std::cout << length << std::endl;
}

void redrawFrame(sf::RenderWindow &window, sf::VertexArray(&line))
{
    window.clear(sf::Color::White);
    window.draw(line);
    window.display();
}