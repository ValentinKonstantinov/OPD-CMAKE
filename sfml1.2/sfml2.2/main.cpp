#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;
    float angleC = 0;
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Ellipse",
        sf::Style::Default, settings);

    sf::ConvexShape ellipse;
    ellipse.setPosition({400, 320});
    ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    ellipse.setPointCount(pointCount);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        for (int pointNo = 0; pointNo < pointCount; ++pointNo)
        {
            float angle = float(2 * M_PI * pointNo) / float(pointCount);
            float radius = 200 * sin(6 * angle);
            sf::Vector2f point = {
                radius * std::sin(angle),
                radius * std::cos(angle)};
            ellipse.setPoint(pointNo, point);
        }

        const float time = clock.restart().asSeconds();
        angleC += time;
        float radius = 100;
        sf::Vector2f point = {
            400 + radius * std::sin(angleC),
            320 + radius * std::cos(angleC)};
        ellipse.setPosition(point.x, point.y);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}