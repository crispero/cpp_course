#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);
void onMouseMove(sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
void redrawFrame(sf::RenderWindow &window, sf::VertexArray(&lines));