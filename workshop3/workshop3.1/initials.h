#pragma once
#include "const.h"
#include <SFML/Graphics.hpp>

class Initials : public sf::Drawable
{
public:
  void initBall();
  void initText();
  void update(float deltaTime);

private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  sf::Text text;
  sf::Font font;
  sf::CircleShape ball;
  sf::Vector2f position = START_POSITION;
  sf::Vector2f textPosition = START_TEXT;
  sf::Vector2f speed = START_SPEED;
};
