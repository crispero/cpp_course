#include <SFML/Graphics.hpp> 
#include <SFML/System.hpp> 
#include <SFML/Window.hpp> 

int main() 
{ 
sf::RenderWindow window(sf::VideoMode({600, 400}), "Rectangles and circle"); 

window.clear(); 

sf::RectangleShape shape1; 
shape1.setSize({150, 20}); 
shape1.setRotation(90); 
shape1.setPosition({200, 120}); 
shape1.setFillColor(sf::Color(0xFF, 0x0, 0x0)); 
window.draw(shape1); 

sf::RectangleShape shape2; 
shape2.setSize({120, 20}); 
shape2.setRotation(180); 
shape2.setPosition({250, 120}); 
shape2.setFillColor(sf::Color(0xFF, 0x0, 0x0)); 
window.draw(shape2); 

sf::RectangleShape shape3; 
shape3.setSize({130, 20}); 
shape3.setRotation(90); 
shape3.setPosition({300, 140}); 
shape3.setFillColor(sf::Color(0xFF, 0x0, 0xFF)); 
window.draw(shape3); 

sf::CircleShape shape4(10); 
shape4.setPosition({280, 100}); 
shape4.setFillColor(sf::Color(0xFF, 0x0, 0xFF)); 
window.draw(shape4); 

sf::RectangleShape shape5; 
shape5.setSize({170, 20}); 
shape5.setRotation(-75); 
shape5.setPosition({350, 265}); 
shape5.setFillColor(sf::Color(0xFF, 0xFF, 0x0)); 
window.draw(shape5); 

sf::RectangleShape shape6; 
shape6.setSize({170, 20}); 
shape6.setRotation(70); 
shape6.setPosition({415, 100}); 
shape6.setFillColor(sf::Color(0xFF, 0xFF, 0x0)); 
window.draw(shape6); 

sf::RectangleShape shape7; 
shape7.setSize({60, 15}); 
shape7.setRotation(180); 
shape7.setPosition({440, 210}); 
shape7.setFillColor(sf::Color(0xFF, 0xFF, 0x0)); 
window.draw(shape7); 

window.display(); 
sf::sleep(sf::seconds(5)); 
}