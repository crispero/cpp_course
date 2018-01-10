#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    sf::ConvexShape white;
    sf::ConvexShape pupil;
    sf::Vector2f position;
    float rotation = 0;
};

sf::Vector2f toEuclidian(float x, float y, float angle)
{
    return {x * std::cos(angle), y * std::sin(angle)};
}

float cursorInEye(const sf::Vector2f &mousePosition, const sf::Vector2f &position, float x, float y)
{
    return ((std::pow((mousePosition.x - position.x) / x, 2)) + std::pow((mousePosition.y - position.y) / y, 2));
}

void updateLeftEye(Eye &leftEye)
{
    const sf::Vector2f rotationRadius = {50.f, 90.f};

    const sf::Vector2f whiteLeftEye = toEuclidian(rotationRadius.x, rotationRadius.y, leftEye.rotation);
    leftEye.pupil.setPosition(leftEye.position + whiteLeftEye);
}
void updateRightEye(Eye &rightEye)
{
    const sf::Vector2f rotationRadius = {50.f, 90.f};

    const sf::Vector2f whiteRightEye = toEuclidian(rotationRadius.x, rotationRadius.y, rightEye.rotation);
    rightEye.pupil.setPosition(rightEye.position + whiteRightEye);
}

void initEye(Eye &leftEye, Eye &rightEye)
{
    sf::Vector2f whiteRadius = {50.f, 100.f};
    sf::Vector2f pupilRadius = {10.f, 20.f};
    constexpr int pointCount = 200;

    leftEye.position = {300, 300};
    rightEye.position = {500, 300};

    leftEye.white.setFillColor(sf::Color(255, 255, 255));
    leftEye.white.setPointCount(pointCount);
    leftEye.white.setPosition(leftEye.position);
    rightEye.white.setFillColor(sf::Color(255, 255, 255));
    rightEye.white.setPointCount(pointCount);
    rightEye.white.setPosition(rightEye.position);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            whiteRadius.x * std::sin(angle),
            whiteRadius.y * std::cos(angle)};
        leftEye.white.setPoint(pointNo, point);
        rightEye.white.setPoint(pointNo, point);
    }

    leftEye.pupil.setPointCount(pointCount);
    leftEye.pupil.setFillColor(sf::Color(0, 0, 0));
    rightEye.pupil.setPointCount(pointCount);
    rightEye.pupil.setFillColor(sf::Color(0, 0, 0));
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilRadius.x * std::sin(angle),
            pupilRadius.y * std::cos(angle)};
        leftEye.pupil.setPoint(pointNo, point);
        rightEye.pupil.setPoint(pointNo, point);
    }
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}

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

void update(const sf::Vector2f &mousePosition, Eye &leftEye, Eye &rightEye)
{
    const sf::Vector2f radius = {50.f, 90.f};
    const float ifInLeftEye = cursorInEye(mousePosition, leftEye.white.getPosition(), radius.x, radius.y);

    if (ifInLeftEye > 1.f)
    {
        const sf::Vector2f leftEyeDelta = mousePosition - leftEye.position;
        leftEye.rotation = atan2(leftEyeDelta.y, leftEyeDelta.x);
        updateLeftEye(leftEye);
    }
    else
    {
        leftEye.pupil.setPosition(mousePosition);
    }
    const float ifInRightEye = cursorInEye(mousePosition, rightEye.white.getPosition(), radius.x, radius.y);

    if (ifInRightEye > 1)
    {
        const sf::Vector2f rightEyeDelta = mousePosition - rightEye.position;
        rightEye.rotation = atan2(rightEyeDelta.y, rightEyeDelta.x);
        updateRightEye(rightEye);
    }
    else
    {
        rightEye.pupil.setPosition(mousePosition);
    }
}

void redrawFrame(sf::RenderWindow &window, Eye &leftEye, Eye &rightEye)
{
    window.clear();
    window.draw(leftEye.white);
    window.draw(leftEye.pupil);
    window.draw(rightEye.white);
    window.draw(rightEye.pupil);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    const sf::Vector2f whiteRadius = {10.f, 30.f};
    const sf::Vector2f blackRadius = {4.f, 10.f};

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eyes follows mouse", sf::Style::Default, settings);

    Eye leftEye;
    Eye rightEye;
    sf::Vector2f mousePosition;

    initEye(leftEye, rightEye);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
}