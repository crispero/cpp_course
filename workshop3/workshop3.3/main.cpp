#include "function.h"

void makeLine(sf::VertexArray(&line), sf::Vector2f mousePosition)
{
    line[0].position = mousePosition;
    line[1].position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;
}

int main()
{
    sf::VertexArray line(sf::Lines, 2.0);
    sf::Vector2f mousePosition;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Line",
        sf::Style::Default, settings);

    while (window.isOpen())
    {
        makeLine(line, mousePosition);
        pollEvents(window, mousePosition);
        redrawFrame(window, line);
    }
}