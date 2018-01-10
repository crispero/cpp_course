#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

// Создаем структуру эллипсов
struct Ellipse
{
    ConvexShape white;
    ConvexShape black;
    Vector2f position;
    float rotation = 0;
};

// Переводит  полярные координаты в декартовы
Vector2f toEuclidean(float x, float y, float angle)
{
    return {x * cos(angle), y * sin(angle)};
}

// Обновляет позиции и повороты частей эллипсов согласно текущему состоянию эллипса
void updateEllipseElements(Ellipse &leftEllipse, Ellipse &rightEllipse)
{
    const Vector2f rotationRadius = {30.f, 50.f};

    const Vector2f whiteLeftEllipseOffset = toEuclidean(rotationRadius.x, rotationRadius.y, leftEllipse.rotation);
    leftEllipse.black.setPosition(leftEllipse.position + whiteLeftEllipseOffset);

    const Vector2f whiteRightEllipseOffset = toEuclidean(rotationRadius.x, rotationRadius.y, rightEllipse.rotation);
    rightEllipse.black.setPosition(rightEllipse.position + whiteRightEllipseOffset);
}

// Инициализируем фигуру
void initEllipse(Ellipse &leftEllipse, Ellipse &rightEllipse)
{
    constexpr int pointCount = 200;
    Vector2f whiteRadius = {50.f, 100.f};
    Vector2f blackRadius = {15.f, 20.f};

    leftEllipse.position = {300, 300};
    rightEllipse.position = {500, 300};

    // Объявляем фигуры, которые будут выглядеть как левый и правый белый эллипс
    leftEllipse.white.setFillColor(sf::Color(255, 255, 255));
    leftEllipse.white.setPointCount(pointCount);
    leftEllipse.white.setPosition(leftEllipse.position);
    rightEllipse.white.setFillColor(sf::Color(255, 255, 255));
    rightEllipse.white.setPointCount(pointCount);
    rightEllipse.white.setPosition(rightEllipse.position);

    // Инициализируем вершины белых эллипсов
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        Vector2f point = {
            whiteRadius.x * sin(angle),
            whiteRadius.y * cos(angle)};
        leftEllipse.white.setPoint(pointNo, point);
        rightEllipse.white.setPoint(pointNo, point);
    }

    // Объявляем фигуры, которые будут выглядеть как левый и правый черный эллипс
    leftEllipse.black.setPointCount(pointCount);
    leftEllipse.black.setFillColor(sf::Color(0, 0, 0));
    rightEllipse.black.setPointCount(pointCount);
    rightEllipse.black.setFillColor(sf::Color(0, 0, 0));

    // Инициализируем вершины черных эллипсов
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        Vector2f point = {
            blackRadius.x * sin(angle),
            blackRadius.y * cos(angle)};
        leftEllipse.black.setPoint(pointNo, point);
        rightEllipse.black.setPoint(pointNo, point);
    }

    updateEllipseElements(leftEllipse, rightEllipse);
}

// Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const Event::MouseMoveEvent &event, Vector2f &mousePosition)
{
    cout << "mouse x=" << event.x << ", y=" << event.y << endl;
    mousePosition = {float(event.x), float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле
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

// Обновляет фигуру, указывающую на мышь
void update(const Vector2f &mousePosition, Ellipse &leftEllipse, Ellipse &rightEllipse)
{
    const Vector2f leftEllipseDelta = mousePosition - leftEllipse.position;
    leftEllipse.rotation = atan2(leftEllipseDelta.y, leftEllipseDelta.x);

    const sf::Vector2f leftOffset = toEuclidean(30, 90, leftEllipse.rotation);
    leftEllipse.black.setPosition(leftEllipse.position + leftOffset);
    if (hypot(leftEllipseDelta.x, leftEllipseDelta.y) <= hypot(leftOffset.x, leftOffset.y))
    {
        leftEllipse.black.setPosition(mousePosition);
    }

    const Vector2f rightEllipseDelta = mousePosition - rightEllipse.position;
    rightEllipse.rotation = atan2(rightEllipseDelta.y, rightEllipseDelta.x);

    const Vector2f rightOffset = toEuclidean(30, 90, rightEllipse.rotation);
    rightEllipse.black.setPosition(rightEllipse.position + rightOffset);
    if (hypot(rightEllipseDelta.x, rightEllipseDelta.y) <= hypot(rightOffset.x, rightOffset.y))
    {
        rightEllipse.black.setPosition(mousePosition);
    }
}

// Рисует и выводит один кадр
void redrawFrame(RenderWindow &window, Ellipse &leftEllipse, Ellipse &rightEllipse)
{
    window.clear();
    window.draw(leftEllipse.white);
    window.draw(leftEllipse.black);
    window.draw(rightEllipse.white);
    window.draw(rightEllipse.black);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    const Vector2f whiteRadius = {10.f, 30.f};
    const Vector2f blackRadius = {4.f, 10.f};

    // Создаём окно с параметрами сглаживания
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Eyes",
        Style::Default, settings);

    Ellipse leftEllipse;
    Ellipse rightEllipse;
    Vector2f mousePosition;

    initEllipse(leftEllipse, rightEllipse);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEllipse, rightEllipse);
        redrawFrame(window, leftEllipse, rightEllipse);
    }
}