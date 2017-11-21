#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "yellow arrow", Style::Default, settings);

    ConvexShape arrow;

    arrow.setPosition({400, 300});
    arrow.setPointCount(7);
    arrow.setPoint(0, {60, 0});
    arrow.setPoint(1, {10, -40});
    arrow.setPoint(2, {10, -20});
    arrow.setPoint(3, {-40, -20});
    arrow.setPoint(4, {-40, 20});
    arrow.setPoint(5, {10, 20});
    arrow.setPoint(6, {10, 40});
    arrow.setFillColor(Color(0xFF, 0xFF, 0));
    arrow.setOutlineColor(Color::Black);
    arrow.setOutlineThickness(3);
    arrow.setRotation(-60);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        window.clear(Color::White);
        window.draw(arrow);
        window.display();
    }
}