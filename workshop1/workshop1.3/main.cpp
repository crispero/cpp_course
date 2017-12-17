#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cat");

    Texture texture;
    texture.loadFromFile("./cat.png");

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(300, 400);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear(Color(255, 255, 255));
        window.draw(sprite);
        window.display();
    }
}