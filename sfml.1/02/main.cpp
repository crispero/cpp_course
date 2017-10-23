#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Rectangles and circle");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({ 60, 20 });
    shape1.setRotation(75);
    shape1.setPosition({ 200, 120});
    shape1.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape1);

    sf::CircleShape shape2(48);
    shape2.setPosition({ 260, 120 });
    shape2.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({ 120, 15 });
    shape3.setRotation(-30);
    shape3.setPosition({ 200, 120});
    shape3.setFillColor(sf::Color(0xFF, 0x0, 0xFF));
    window.draw(shape3);

    window.display();
    sf::sleep(sf::seconds(5));
}