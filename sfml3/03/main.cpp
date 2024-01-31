#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}
void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

void pollEvents(sf::RenderWindow &window, sf ::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock, float &speed)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = atan2(delta.y, delta.x);
    float time = clock.restart().asSeconds();
    if (speed > (M_PI + 0.1))
    {
        speed -= 2 * M_PI;
    }
    else if (speed < (-M_PI - 0.1))
    {
        speed += 2 * M_PI;
    };
    const float min = 0.26;
    if ((angle >= 0 && speed >= 0) || (angle < 0 && speed < 0))
    {
        if (angle > speed)
        {
            speed += min * time;
        }
        else if (angle < speed)
        {
            speed -= min * time;
        }
    }
    else if (angle >= 0 && speed < 0)
    {
        if (fabs(angle) + fabs(speed) < M_PI)
        {

            speed += min * time;
        }
        else
        {
            speed -= min * time;
        }
    }
    else if (angle < 0 && speed >= 0)
    {
        if (fabs(angle) + fabs(speed) < M_PI)
        {
            speed -= min * time;
        }
        else
        {
            speed += min * time;
        }
    }

    pointer.setRotation(toDegrees(speed));
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Clock clock;
    float speed;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse", sf::Style::Default, settings);
    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;
    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, clock, speed);
        redrawFrame(window, pointer);
    }
}