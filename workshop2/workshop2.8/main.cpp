#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <cassert>
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

// Сравнение с допустимой абсолютной погрешностью
bool areCloseAbsolute(float firstArgument, float secondArgument, float tolerance = 0.001f)
{
    return abs(firstArgument - secondArgument) < tolerance;
}

// Сравнение с допустимой относительной погрешностью
bool areCloseRelative(float firstArgument, float secondArgument, float tolerance = 0.001f)
{
    return abs((firstArgument - secondArgument) / secondArgument) < tolerance;
}

// Сравнение двух чисел с плавающей точкой с допустимой погрешностью 0.001
bool areFuzzyEqual(float firstArgument, float secondArgument)
{
    constexpr float tolerance = 0.001f;
    if (abs(secondArgument) > 1.f)
    {
        return areCloseRelative(firstArgument, secondArgument, tolerance);
    }
    return areCloseAbsolute(firstArgument, secondArgument, tolerance);
}

bool areVectorFuzzyEqual(Vector2f firstArgument, Vector2f secondArgument)
{
    bool areFirstArgumentEqual = areFuzzyEqual(firstArgument.x, secondArgument.x);
    bool areSecondArgumentEqual = areFuzzyEqual(firstArgument.y, secondArgument.y);
}

Vector2f getImpulse(vector<Ball> &balls)
{
    Vector2f impulse;
    for (int i = 0; i < size(balls); ++i)
    {
        impulse += balls[i].speed;
    }
    return impulse;
}

float getEnergy(vector<Ball> &balls, const unsigned BALL_SIZE)
{
    float energy;
    for (int i = 0; i < size(balls); ++i)
    {
        energy += pow(BALL_SIZE, 3) * (pow(balls[i].speed.x, 2) + pow(balls[i].speed.y, 2));
    }
    return energy;
}

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

size_t getRandomIndex(PRNG &generator, size_t size)
{
    uniform_int_distribution<size_t> distribution(0, size - 1);
    return distribution(generator.engine);
}

Color getRandomColor(PRNG &generator, vector<Color> &colors)
{
    const unsigned firstIndexColor = getRandomIndex(generator, colors.size());
    const unsigned secondIndexColor = getRandomIndex(generator, colors.size());

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

void ballCollision(vector<Ball> &balls, const unsigned BALL_SIZE)
{
    float oldEnergy = getEnergy(balls, BALL_SIZE);
    Vector2f oldImpulse = getImpulse(balls);
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
    Vector2f newImpulse = getImpulse(balls);
    float newEnergy = getEnergy(balls, BALL_SIZE);
    assert(areVectorFuzzyEqual(newImpulse, oldImpulse));
    assert(areFuzzyEqual(newEnergy, oldEnergy));
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
    ballCollision(balls, BALL_SIZE);
}

void initNewBall(Event::MouseButtonEvent &event, vector<Ball> &balls, const unsigned BALL_SIZE, vector<Color> &colors)
{
    Vector2f mousePosition = {float(event.x) - (BALL_SIZE / 2), float(event.y) - (BALL_SIZE / 2)};
    bool canInitBall = true;
    for (int i = 0; i < size(balls); ++i)
    {
        Vector2f delta = mousePosition - balls[i].ball.getPosition();
        float distance = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
        if (distance <= 2 * BALL_SIZE)
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

        newBall.ball.setRadius(BALL_SIZE);
        newBall.ball.setPosition(mousePosition);
        getRandomBall(generator, balls, colors);
        float speedX = getRandomFloat(generator);
        float speedY = getRandomFloat(generator);
        newBall.speed = {speedX, speedY};
        balls.push_back(newBall);
    }
}

void pollEvents(RenderWindow &window, vector<Ball> &balls, vector<Color> &colors, const float BALL_SIZE)
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
            initNewBall(event.mouseButton, balls, BALL_SIZE, colors);
            break;
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
    constexpr unsigned interval = 10;

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
        pollEvents(window, balls, colors, BALL_SIZE);
        float deltaTime = clock.restart().asSeconds() / interval;
        redrawFrame(window, balls);
        for (int i = 1; i < interval; ++i)
        {
            update(balls, deltaTime);
        }
    }
}
