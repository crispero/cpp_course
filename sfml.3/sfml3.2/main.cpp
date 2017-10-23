#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

constexpr int pointCount = 200;
const Vector2f ellipse2Radius = {70.f, 130.f};
const Vector2f ellipse1Radius = {20.f, 30.f};

struct Ellipse
{
    ConvexShape ellipse2;
    ConvexShape ellipse1;
    Vector2f position;
    float rotation = 0;
};

void initEllipse(Ellipse &ellipse)
{
    // Объявляем фигуру, которая будет выглядеть как эллипс2
    ellipse.ellipse2.setPosition({300, 320});
    ellipse.ellipse2.setFillColor(Color(0xFF, 0xFF, 0xFF));

    // Инициализируем вершины псевдо-эллипса 2
    ellipse.ellipse2.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        Vector2f point = {
            ellipse2Radius.x * std::sin(angle),
            ellipse2Radius.y * std::cos(angle)};
        ellipse.ellipse2.setPoint(pointNo, point);
    }

    // Объявляем фигуру, которая будет выглядеть как эллипс1
    ellipse.ellipse1.setPosition({300, 320});
    ellipse.ellipse1.setFillColor(Color(0xFF, 0x00, 0x00));

    // Инициализируем вершины псевдо-эллипса1
    ellipse.ellipse1.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        Vector2f point = {
            ellipse1Radius.x * std::sin(angle),
            ellipse1Radius.y * std::cos(angle)};
        ellipse.ellipse1.setPoint(pointNo, point);
    }
}

// Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const Event::MouseMoveEvent &event, Vector2f &mousePosition)
{
    cout << "mouse x=" << event.x << ", y=" << event.y << endl;
    mousePosition = {float(event.x), float(event.y)};
}

// Обновляет позиции и повороты частей эллипса согласно текущему состоянию стрелки
void updateEllipseElements(Ellipse &ellipse)
{
    const Vector2f ellipse1Offset = (300, ellipse.rotation);
    ellipse.ellipse1.setPosition(ellipse.position + ellipse1Offset);
    ellipse.ellipse1.setRotation(toDegrees(ellipse.rotation));
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
void update(const sf::Vector2f &mousePosition, Ellipse &ellipse)
{
    const sf::Vector2f delta = mousePosition - ellipse1.position;
    ellipse1.rotation = atan2(delta.y, delta.x);
    updateEllipseElements(ellipse);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Ellipse &ellipse)
{
    window.clear();
    window.draw(ellipse.ellipse2);
    window.draw(ellipse.ellipse1);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    // Создаём окно с параметрами сглаживания
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Ellipse and ellipse1",
        Style::Default, settings);

    Ellipse ellipse;
    Vector2f mousePosition;

    initEllipse(ellipse);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, ellipse);
        redrawFrame(window, ellipse);
    }
}