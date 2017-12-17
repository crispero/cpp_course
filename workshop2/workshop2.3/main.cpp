#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <random>

using namespace std;
using namespace sf;

struct Ball
{
    CircleShape ball;
    Vector2f position;
    Vector2f speed;
};

struct PRNG
{
    mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(time(nullptr));
    generator.engine.seed(seed);
}

float getRandomSpeed(PRNG &generator)
{
    uniform_int_distribution<int> distribution(0, 200);
    return distribution(generator.engine);
}
void update(Ball (&balls)[6], float deltaTime, const unsigned WINDOW_WIDTH = 800, const unsigned WINDOW_HEIGHT = 600, const unsigned BALL_SIZE = 30)
{
    for (int i = 1; i < size(balls); ++i)
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

    for (int fi = 1; fi < size(balls); ++fi)
    {
        for (int si = fi + 1; si < size(balls); ++si)
        {
            Vector2f deltaPosition = balls[si].position - balls[fi].position;
            Vector2f deltaSpeed = balls[si].speed - balls[fi].speed;
            float distance = sqrt(pow(deltaPosition.x, 2) + pow(deltaPosition.y, 2));
            float modification = ((deltaPosition.x * deltaSpeed.x) + (deltaPosition.y * deltaSpeed.y)) / pow(distance, 2);
            if (distance <= (2 * BALL_SIZE))
            {

                balls[fi].speed = balls[fi].speed + modification * deltaPosition;
                balls[si].speed = balls[si].speed - modification * deltaPosition;
            }
        }
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

void redrawFrame(RenderWindow &window, Ball (&balls)[6])
{
    window.clear();
    for (int i = 1; i < size(balls); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

int main()
{
    Ball balls[6];
    PRNG generator;
    initGenerator(generator);

    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned BALL_SIZE = 30;

    for (int i = 1; i < size(balls); ++i)
    {
        balls[i].ball.setPosition(100 * i, 100 * i);
        balls[i].ball.setFillColor(Color{40, 255, 255});
        balls[i].ball.setRadius(BALL_SIZE);
        float speedX = getRandomSpeed(generator);
        float speedY = getRandomSpeed(generator);
        balls[i].speed = {speedX, speedY};
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
