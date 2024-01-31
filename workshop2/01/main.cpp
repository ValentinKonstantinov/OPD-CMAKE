#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <stdlib.h>
#include <time.h>

struct Ball
{
    sf::Clock &clock;
    sf::Texture texture;

    sf::Sprite sprite;

    sf::Vector2f position;
    sf::Vector2f speed;

    //float rotation;
    float BALL_SIZE;
    Ball(sf::Clock &clock)
        : clock(clock)
    {
    }
};

int GetRandomNumber(int min, int max)
{
    // Установить генератор случайных чисел
    srand(time(NULL));

    // Получить случайное число - формула
    int num = min + rand() % (max - min + 1);

    return num;
}

initBall(std::vector<Ball> &BallsObject, Ball &ball, sf::Clock &clock)
{
    float maxCat = 10;
    int colorA = 20;
    int colorB;
    int colorC;
    float i = 1;
    float positonInitX;
    float positonInitY;
    positonInitX = GetRandomNumber(0, GetRandomNumber(0, 600));

    positonInitY = GetRandomNumber(0, GetRandomNumber(0, 600));

    if (!ball.texture.loadFromFile("../cat.png"))
    {
        std::cout << "not texture cat" << std::endl;
    };
    ball.sprite.setTexture(ball.texture);
    ball.speed = {50.f, 50.f};
    ball.BALL_SIZE = 20;

    while (i <= 10)
    {
        colorA = colorA + 15;
        colorB = colorA + GetRandomNumber(0, colorA);
        colorC = colorA + GetRandomNumber(0, colorA);

        ball.sprite.setColor(sf::Color(colorA, colorB, colorC));
        positonInitX = GetRandomNumber(0, GetRandomNumber(positonInitX - GetRandomNumber(0, 200), 500));
        positonInitY = GetRandomNumber(0, GetRandomNumber(0, positonInitY + GetRandomNumber(0, 200)));

        ball.position = {positonInitX, positonInitY};
        ball.sprite.setPosition(ball.position);
        BallsObject.push_back(ball);

        i = i + 1;
    };
};

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving Balls");
    sf::Clock clock;

    std::vector<Ball> BallsObject;
    Ball ball(clock);
    initBall(BallsObject, ball, clock);

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

        const float dt = clock.restart().asSeconds();
        for (size_t i = 0; i < BallsObject.size(); ++i)
        {
            Ball ball = BallsObject[i];
            sf::Vector2f position = ball.position;
            sf::Vector2f speed = ball.speed;
            const float size = ball.BALL_SIZE;
            position += speed * dt;

            if ((position.x + 2 * size >= WINDOW_WIDTH) && (speed.x > 0))
            {
                speed.x = -speed.x;
                ball.sprite.setScale(-1, 1);
            };
            if ((position.x < 0) && (speed.x < 0))
            {
                speed.x = -speed.x;
                ball.sprite.setScale(1, 1);
            };
            if ((position.y + 2 * size >= WINDOW_HEIGHT) && (speed.y > 0))
            {
                speed.y = -speed.y;
            };
            if ((position.y < 0) && (speed.y < 0))
            {
                speed.y = -speed.y;
            };
            ball.position = position;
            ball.speed = speed;
            ball.sprite.setPosition(ball.position);
            BallsObject[i].position = ball.position;
            BallsObject[i].speed = ball.speed;
            BallsObject[i].sprite = ball.sprite;
            // BallsObject.pop_back();
            // BallsObject.push_back(ball);
        }
        for (size_t fi = 0; fi < BallsObject.size(); ++fi)
        {
            for (size_t si = fi + 1; si < BallsObject.size(); ++si)
            {
                // проверяем столкновение fi, si
                const sf::Vector2f Position = BallsObject[fi].position - BallsObject[si].position;
                float deltaPosition = Position.x * Position.x + Position.y * Position.y;
                deltaPosition = sqrt(deltaPosition);
                if (deltaPosition < (BallsObject[fi].BALL_SIZE + BallsObject[si].BALL_SIZE))
                {
                    sf::Vector2f Position = BallsObject[si].position - BallsObject[fi].position;
                    deltaPosition = Position.x * Position.x + Position.y * Position.y;
                    deltaPosition = sqrt(deltaPosition);
                    sf::Vector2f Speed = BallsObject[fi].speed - BallsObject[si].speed;
                    float deltaSpeed = Speed.x * Speed.x + Speed.y * Speed.y;
                    deltaSpeed = sqrt(deltaSpeed);
                    float rotation = atan2(deltaPosition, deltaSpeed);
                    float fabsX = fabs(Speed.x);
                    float fabsY = fabs(Speed.y);
                    sf::Vector2f fabsSpeed = {fabsX, fabsY};
                    fabsX = fabs(Position.x);
                    fabsY = fabs(Position.y);
                    sf::Vector2f fabsPosition = {fabsX, fabsY};
                    sf::Vector2f dotMultiplicator;
                    dotMultiplicator.x = Position.x * Speed.x + Speed.y * Position.y;
                    dotMultiplicator.y = Position.x * Speed.x + Speed.y * Position.y;
                    dotMultiplicator.x = dotMultiplicator.x * Position.x / (Position.x * Position.x + Position.y * Position.y);
                    dotMultiplicator.y = dotMultiplicator.y * Position.y / (Position.x * Position.x + Position.y * Position.y);
                    BallsObject[fi].speed = BallsObject[fi].speed - dotMultiplicator;

                    Position = BallsObject[fi].position - BallsObject[si].position;
                    deltaPosition = Position.x * Position.x + Position.y * Position.y;
                    deltaPosition = sqrt(deltaPosition);
                    Speed = BallsObject[si].speed - BallsObject[fi].speed;
                    deltaSpeed = Speed.x * Speed.x + Speed.y * Speed.y;
                    deltaSpeed = sqrt(deltaSpeed);
                    rotation = atan2(deltaPosition, deltaSpeed);
                    fabsX = fabs(Speed.x);
                    fabsY = fabs(Speed.y);
                    fabsSpeed = {fabsX, fabsY};
                    fabsX = fabs(Position.x);
                    fabsY = fabs(Position.y);
                    fabsPosition = {fabsX, fabsY};
                    dotMultiplicator.x = Position.x * Speed.x + Speed.y * Position.y;
                    dotMultiplicator.y = Position.x * Speed.x + Speed.y * Position.y;
                    dotMultiplicator.x = dotMultiplicator.x * Position.x / (Position.x * Position.x + Position.y * Position.y);
                    dotMultiplicator.y = dotMultiplicator.y * Position.y / (Position.x * Position.x + Position.y * Position.y);
                    BallsObject[si].speed = BallsObject[si].speed - dotMultiplicator;
                }
            }
        }

        window.clear(sf::Color(255, 255, 255));
        for (size_t i = 0; i < BallsObject.size(); ++i)
        {
            window.draw(BallsObject[i].sprite);
        }
        window.display();
    }
}