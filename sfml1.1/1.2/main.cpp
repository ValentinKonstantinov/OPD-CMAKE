#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangles and circle");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({120, 20});
    shape1.setRotation(90);
    shape1.setPosition({100, 120});
    shape1.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape1);

    sf::RectangleShape shape3;
    shape3.setSize({80, 20});
    shape3.setRotation(-45);
    shape3.setPosition({100, 180});
    shape3.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({80, 20});
    shape4.setRotation(35);
    shape4.setPosition({100, 180});
    shape4.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({120, 20});
    shape5.setRotation(70);
    shape5.setPosition({200, 120});
    shape5.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({120, 20});
    shape6.setRotation(-70);
    shape6.setPosition({220, 235});
    shape6.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({120, 20});
    shape7.setRotation(-90);
    shape7.setPosition({300, 240});
    shape7.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape7);
    window.display();

    sf::sleep(sf::seconds(5));
}