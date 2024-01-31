#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

float radius = 0;

struct Arrow
{
    sf::ConvexShape heptagon;
    sf::Vector2f position;
    float rotation = 0;
};

sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        radius * cos(angle),
        radius * sin(angle)};
}
//переводим радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

//обновляет позиции и повороты частей стрелки согласно
// текущему состоянию стрелки
void updateArrowElements(Arrow &arrow, sf::Clock &clock) //обновление положения элемента
{
    if (radius > 20)
    {
        radius = 20;
    }

    const sf::Vector2f headOffset = toEuclidean(radius, arrow.rotation);
    float time = clock.restart().asSeconds();
    float speed = 100;
    float T = time;

    arrow.heptagon.setPosition(arrow.position + headOffset * T);
    arrow.position = arrow.position + headOffset * T;
    //arrow.rotation = arrow.rotation * T * 100;
    arrow.heptagon.setRotation(toDegrees(arrow.rotation));
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}
// Инициализирует фигуру-стрелку

void initArrow(Arrow &arrow, sf::Clock &clock) //инициализирует структуру
{
    arrow.position = {400, 300};
    arrow.rotation = -1.5;
    arrow.heptagon.setPointCount(7);
    arrow.heptagon.setPoint(0, {140, 0});
    arrow.heptagon.setPoint(1, {70, -80});
    arrow.heptagon.setPoint(2, {70, -40});
    arrow.heptagon.setPoint(3, {0, -40});
    arrow.heptagon.setPoint(4, {0, 40});
    arrow.heptagon.setPoint(5, {70, 40});
    arrow.heptagon.setPoint(6, {70, 80});
    arrow.heptagon.setFillColor(sf::Color(248, 243, 43));

    arrow.heptagon.setOutlineColor(sf::Color(0, 0, 50));
    arrow.heptagon.setOutlineThickness(-5);

    updateArrowElements(arrow, clock);
}

// Опрашивает и обрабатывает доступные события в цикле.
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
// Обновляет фигуру, указывающую на мышь
//переводим полярные координаты в декартовы
void update(const sf::Vector2f &mousePosition, Arrow &arrow, sf::Clock &clock)
{
    const sf::Vector2f delta = mousePosition - arrow.position;
    arrow.rotation = atan2(delta.y, delta.x);

    radius = delta.x * delta.x + delta.y * delta.y;
    radius = sqrt(radius);

    updateArrowElements(arrow, clock);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Arrow &arrow)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(arrow.heptagon);

    window.display();
    //  window.draw(arrow.ellipseInternal);
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Clock clock;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    Arrow arrow;

    sf::Vector2f mousePosition;

    initArrow(arrow, clock);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, arrow, clock);
        redrawFrame(window, arrow);
    }
}