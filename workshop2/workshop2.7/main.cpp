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
    float liveDuration = 10.f;
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
float getRandomFloat(PRNG &generator)
{
    uniform_real_distribution<float> distribution(-200, 200);
    return distribution(generator.engine);
}

unsigned getRandomIndex(PRNG &generator)
{
    uniform_int_distribution<size_t> distribution(0, 7);
    return distribution(generator.engine);
}

Color getRandomColor(PRNG &generator, vector<Color> &colors)
{
    const unsigned firstIndexColor = getRandomIndex(generator);
    const unsigned secondIndexColor = getRandomIndex(generator);

    Color firstColor = colors[firstIndexColor];
    Color secondColor = colors[secondIndexColor];

    Color randomColor;
    randomColor.r = firstColor.r + secondColor.r;
    randomColor.g = firstColor.g + secondColor.g;
    randomColor.b = firstColor.b + secondColor.b;
    return randomColor;
}

void getRandomBall(PRNG &generator, vector<Ball> &balls, vector<Color> &colors)
{
    for (int i = 0; i < size(balls); ++i)
    {
        balls[i].ball.setFillColor(getRandomColor(generator, colors));
    }
}

auto removeBalls = [&](Ball balls) {
    return balls.liveDuration <= 0;
};

void removeDeathBalls(vector<Ball> &balls)
{
    auto iterator = remove_if(balls.begin(), balls.end(), removeBalls);
    balls.erase(iterator, balls.end());
}

void update(vector<Ball> &balls, float deltaTime, const unsigned WINDOW_WIDTH = 800, const unsigned WINDOW_HEIGHT = 600, const unsigned BALL_SIZE = 30)
{
    removeDeathBalls(balls);
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
        balls[i].liveDuration -= deltaTime;
    }

    for (int fi = 0; fi < size(balls); ++fi)
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

void initNewBall(Event::MouseButtonEvent &event, vector<Ball> &balls, vector<Color> &colors, PRNG &generator)
{
    Vector2f mousePosition = {float(event.x), float(event.y)};
    bool canInitBall = true;
    for (int i = 0; i < size(balls); ++i)
    {
        Vector2f delta = balls[i].ball.getPosition() - mousePosition;
        float distance = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
        if (distance <= 60)
        {
            canInitBall = false;
        }
    }
    if (canInitBall)
    {
        PRNG generator;
        initGenerator;
        Color color;
        Ball newBall;

        newBall.ball.setRadius(30);
        newBall.ball.setPosition(mousePosition);
        getRandomBall(generator, balls, colors);
        float speedX = getRandomFloat(generator);
        float speedY = getRandomFloat(generator);
        newBall.speed = {speedX, speedY};
        balls.push_back(newBall);
    }
}

void pollEvents(RenderWindow &window, vector<Ball> &balls, vector<Color> &colors, PRNG &generator)
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
            initNewBall(event.mouseButton, balls, colors, generator);
        default:
            break;
        }
    }
}

void redrawFrame(RenderWindow &window, vector<Ball> &balls)
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
    vector<Ball> balls;
    PRNG generator;
    initGenerator(generator);

    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned BALL_SIZE = 30;

    Clock clock;

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Ball",
        Style::Default, settings);

    vector<Color> colors = {
        {57, 89, 255},
        {98, 57, 138},
        {67, 36, 213},
        {10, 176, 45},
        {94, 217, 249},
        {123, 32, 245},
        {38, 21, 32},
        {111, 222, 99}};

    vector<Vector2f> speed = {
        {50, 190},
        {67, 59},
        {200, 115},
        {87, 58},
        {23, 182},
        {73, 171},
        {145, 30},
        {84, 90}};

    while (window.isOpen())
    {
        pollEvents(window, balls, colors, generator);
        float deltaTime = clock.restart().asSeconds() / 7;
        redrawFrame(window, balls);
        for (int i = 1; i < 7; ++i)
        {
            update(balls, deltaTime);
        }
    }
}
