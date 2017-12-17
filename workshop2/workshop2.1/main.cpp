#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

using namespace std;
using namespace sf;

struct Ball
{
    CircleShape ball;
    Vector2f speed;
    Vector2f position;
};

void update(Ball (&balls)[5], float deltaTime, const unsigned WINDOW_WIDTH = 800, const unsigned WINDOW_HEIGHT = 600, const unsigned BALL_SIZE = 30)
{
    for (int i = 0; i < size(balls); ++i)
    {
        balls[i].position = balls[i].ball.getPosition();
        balls[i].position += balls[i].speed * deltaTime;
        if (balls[i].position.x + 2 * BALL_SIZE >= WINDOW_WIDTH)
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if (balls[i].position.x <= 0)
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if (balls[i].position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT)
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if (balls[i].position.y <= 0)
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        balls[i].ball.setPosition(balls[i].position);
    }
}

void pollEvents(RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void redrawFrame(RenderWindow &window, Ball (&balls)[5])
{
    window.clear();
    for (int i = 0; i < size(balls); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

int main()
{

    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned BALL_SIZE = 30;

    Ball balls[5];

    for (int i = 0; i < size(balls); ++i)
    {
        balls[i].ball.setPosition(100 * i, 100 * i);
        balls[i].ball.setFillColor(Color{40, 255, 255});
        balls[i].ball.setRadius(BALL_SIZE);
        balls[i].speed = {100.f * i, 100.f};
    }

    Clock clock;

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Ball",
        Style::Default, settings);

    while (window.isOpen())
    {
        pollEvents(window);
        float deltaTime = clock.restart().asSeconds();
        redrawFrame(window, balls);
        update(balls, deltaTime);
    }
}
