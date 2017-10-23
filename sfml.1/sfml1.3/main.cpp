#include <SFML/Graphics.hpp> 
#include <SFML/System.hpp> 
#include <SFML/Window.hpp> 

int main() 
{ 
sf::RenderWindow window(sf::VideoMode({800, 800}), "Rectangles, circle and convex"); 

window.clear(); 

sf::RectangleShape shape1; 
shape1.setSize({300, 500}); 
shape1.setRotation(90); 
shape1.setPosition({650, 300}); 
shape1.setFillColor(sf::Color(0x8B, 0x45, 0x13)); 
window.draw(shape1); 

sf::RectangleShape shape2; 
shape2.setSize({200, 100}); 
shape2.setRotation(90); 
shape2.setPosition({300, 400}); 
shape2.setFillColor(sf::Color(0x1C, 0x1C, 0x1C)); 
window.draw(shape2); 

sf::ConvexShape trapeze; 
trapeze.setFillColor(sf::Color(0x61, 0x0B, 0x0B)); 
trapeze.setPosition({400, 210}); 
trapeze.setPointCount(4); 
trapeze.setPoint(0, {-150, 0}); 
trapeze.setPoint(1, {+150, 0}); 
trapeze.setPoint(2, {+300, 120}); 
trapeze.setPoint(3, {-300, 120}); 

sf::RectangleShape shape3; 
shape3.setSize({80, 40}); 
shape3.setRotation(90); 
shape3.setPosition({535, 190}); 
shape3.setFillColor(sf::Color(0x36, 0x36, 0x36)); 
window.draw(shape3); 

sf::RectangleShape shape4; 
shape4.setSize({70, 50}); 
shape4.setRotation(180); 
shape4.setPosition({550, 200}); 
shape4.setFillColor(sf::Color(0x36, 0x36, 0x36)); 
window.draw(shape4); 

sf::CircleShape shape5(18); 
shape5.setPosition({510, 120}); 
shape5.setFillColor(sf::Color(0xB5, 0xB5, 0xB5)); 
window.draw(shape5); 

sf::CircleShape shape6(20); 
shape6.setPosition({520, 95}); 
shape6.setFillColor(sf::Color(0xB5, 0xB5, 0xB5)); 
window.draw(shape6); 

sf::CircleShape shape7(25); 
shape7.setPosition({540, 65}); 
shape7.setFillColor(sf::Color(0xB5, 0xB5, 0xB5)); 
window.draw(shape7); 

sf::CircleShape shape8(28); 
shape8.setPosition({560, 30}); 
shape8.setFillColor(sf::Color(0xB5, 0xB5, 0xB5)); 
window.draw(shape8); 

window.draw(trapeze); 
window.draw(shape4); 
window.draw(shape3); 
window.display(); 
sf::sleep(sf::seconds(5)); 
}