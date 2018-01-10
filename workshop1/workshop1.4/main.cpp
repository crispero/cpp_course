#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace sf;

struct Cat
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f scale;
    sf::Vector2f position;
};

struct Laser
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f scale;
    sf::Vector2f position;
};

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void init(Cat &cat, Laser &laser)
{
    cat.texture.loadFromFile("./cat.png");

    cat.sprite.setTexture(cat.texture);
    cat.sprite.setPosition(30, 30);

    laser.texture.loadFromFile("./red_pointer.png");
    laser.sprite.setTexture(laser.texture);
}

void onMouseClick(Event::MouseButtonEvent &event, Vector2f &mousePosition, Laser &laser)
{
    laser.scale = {1, 1};
    mousePosition = {float(event.x), float(event.y)};
    laser.sprite.setPosition(mousePosition);
}

void pollEvents(RenderWindow &window, Vector2f &mousePosition, Laser &laser)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        case Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, mousePosition, laser);
            break;
        default:
            break;
        }
    }
}

void update(sf::Vector2f &mousePosition, Cat &cat, Laser &laser, float deltaTime)
{
    const sf::Vector2f delta = mousePosition - cat.position;
    float angle = atan2(delta.y, delta.x);
    sf::Vector2f direction = {0, 0};
    float speed = 100.f;
    if (angle < 0)
    {
        angle += float(2 * M_PI);
    }
    angle = toDegrees(angle);

    if (((angle >= 0) && (angle < 90)) || ((angle <= 360) && (angle > 270)))
    {
        cat.sprite.setScale(1, 1);
    }
    else
    {
        cat.sprite.setScale(-1, 1);
    }

    if (hypotf(delta.x, delta.y) != 0.f)
    {
        direction = (delta / hypotf(delta.x, delta.y));
    }

    speed = std::min(hypotf(delta.x, delta.y), speed * deltaTime);

    cat.position += direction * speed;
    cat.sprite.setPosition(cat.position);
    cat.sprite.setScale(cat.sprite.getScale());
}

void redrawFrame(RenderWindow &window, Cat &cat, Laser &laser)
{
    window.clear(Color::White);
    window.draw(cat.sprite);
    window.draw(laser.sprite);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    Cat cat;
    Laser laser;

    init(cat, laser);

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Cat and laser", Style::Default, settings);

    Clock clock;
    Vector2f mousePosition;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition, laser);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, cat, laser, deltaTime);
        redrawFrame(window, cat, laser);
    }
}