#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;
    float x;
    float speed = 100.f;
    float time = 0;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;
    const sf::Vector2f position = {10, 350};

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

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

        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        time += clock.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float y = amplitudeY * std::sin(wavePhase / periodY);

        const float dt = clock.restart().asSeconds();
        x += speed * dt;

        if ((x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed > 0))
        {
            speed = -speed;
        }
        if ((x < 0) && (speed < 0))
        {
            speed = -speed;
        }

        const sf::Vector2f offset = {x, y};

        ball.setPosition(position + offset);

        window.clear();
        window.draw(ball);
        window.display();
    }
}