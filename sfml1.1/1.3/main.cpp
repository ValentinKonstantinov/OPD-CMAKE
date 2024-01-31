#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{

    sf::RectangleShape shape1;
    shape1.setSize({500, 300});
    shape1.setRotation(00);
    shape1.setPosition({100, 250});
    shape1.setFillColor(sf::Color(0x8B, 0x45, 0x13));

    sf::RectangleShape shape2;
    shape2.setSize({100, 150});
    shape2.setRotation(00);
    shape2.setPosition({200, 400});
    shape2.setFillColor(sf::Color(0x0, 0x0, 0x0));

    sf::ConvexShape trapeze;
    trapeze.setFillColor(sf::Color(0x80, 0x0, 0x0));
    trapeze.setPosition({350, 150});
    trapeze.setPointCount(4);
    trapeze.setPoint(0, {-150, 0});
    trapeze.setPoint(1, {+150, 0});
    trapeze.setPoint(2, {+300, 150});
    trapeze.setPoint(3, {-300, 150});

    sf::RectangleShape shape3;
    shape3.setSize({50, 100});
    shape3.setRotation(00);
    shape3.setPosition({400, 100});
    shape3.setFillColor(sf::Color(0x80, 0x80, 0x80));

    sf::RectangleShape shape4;
    shape4.setSize({75, 40});
    shape4.setRotation(00);
    shape4.setPosition({387, 85});
    shape4.setFillColor(sf::Color(0x80, 0x80, 0x80));

    sf::CircleShape shape5(20);
    shape5.setPosition({410, 60});
    shape5.setFillColor(sf::Color(0xA9, 0xA9, 0xA9));

    sf::CircleShape shape6(25);
    shape6.setPosition({440, 40});
    shape6.setFillColor(sf::Color(0xA9, 0xA9, 0xA9));

    sf::CircleShape shape7(30);
    shape7.setPosition({470, 25});
    shape7.setFillColor(sf::Color(0xA9, 0xA9, 0xA9));

    sf::CircleShape shape8(40);
    shape8.setPosition({510, 15});
    shape8.setFillColor(sf::Color(0xA9, 0xA9, 0xA9));

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Home");
    window.clear();
    window.draw(shape1);
    window.draw(shape2);
    window.draw(trapeze);
    window.draw(shape3);
    window.draw(shape5);
    window.draw(shape6);
    window.draw(shape7);
    window.draw(shape8);
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}