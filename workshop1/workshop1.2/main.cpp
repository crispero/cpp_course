#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace sf;

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const Event::MouseMoveEvent &event, Vector2f &mousePosition)
{
    cout << "mouse x=" << event.x << ", y=" << event.y << endl;

    mousePosition = {float(event.x), float(event.y)};
}
void pollEvents(RenderWindow &window, Vector2f &mousePosition)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        case Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const Vector2f &mousePosition, ConvexShape &arrow, float &deltaTime)
{
    const Vector2f delta = mousePosition - arrow.getPosition();
    float angle = atan2(delta.y, delta.x);
    Vector2f direction = (delta / hypotf(delta.x, delta.y));
    float speed = 20.f;
    if ((delta.x, delta.y) != 0.f)
    {
        arrow.setPosition(arrow.getPosition() + direction * deltaTime * speed);
    }
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float maxRotation = 90 * deltaTime;
    const float rotation = abs(angle - arrow.getRotation());
    if (angle != arrow.getRotation())
    {
        if (angle > arrow.getRotation())
        {
            if ((angle - 180) > arrow.getRotation())
            {
                arrow.setRotation(arrow.getRotation() - min(maxRotation, rotation));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() + min(maxRotation, rotation));
            }
        }

        else
        {
            if ((angle + 180) < arrow.getRotation())
            {
                arrow.setRotation(arrow.getRotation() + min(maxRotation, rotation));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() - min(maxRotation, rotation));
            }
        }
    }
}

void redrawFrame(RenderWindow &window, ConvexShape &arrow)
{
    window.clear();
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow ", Style::Default, settings);

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

    Clock clock;
    Vector2f mousePosition;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, arrow, deltaTime);
        redrawFrame(window, arrow);
    }
}