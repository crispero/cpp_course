#include "initials.h"

void Initials::initBall()
{
    ball.setPosition(position);
    ball.setRadius(BALL_SIZE);
    ball.setFillColor(sf::Color::Yellow);
    ball.setOutlineThickness(OUTLINE_SIZE);
    ball.setOutlineColor(sf::Color::Red);
}

void Initials::initText()
{
    font.loadFromFile("./arial.ttf");
    text.setFont(font);
    text.setPosition(position);
    text.setString("TIA");
    text.setFillColor(sf::Color::Black);
}

void Initials::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(ball, states);
    target.draw(text, states);
}

void Initials::update(float deltaTime)
{
    if (position.y + 2 * BALL_SIZE > WINDOW_HEIGHT)
    {
        speed.y = -speed.y;
    }

    speed.y += FALLING_ACCELERATION * deltaTime;
    position += speed * deltaTime;
    textPosition += speed * deltaTime;
    ball.setPosition(position);
    text.setPosition(textPosition);
}