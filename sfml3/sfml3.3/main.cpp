#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
float RadiusL = 0;
float RadiusR = 0;

struct Arrow
{
    sf::ConvexShape ellipseLeft;
    sf::ConvexShape ellipseRight;
    sf::ConvexShape ellipseLeftFon;
    sf::ConvexShape ellipseRightFon;

    sf::Vector2f ellipseRightFonPosition;
    sf::Vector2f ellipseLeftFonPosition;
    sf::Vector2f ellipseRightPosition;
    sf::Vector2f ellipseLeftPosition;
    float rotationLeft = 0;
    float rotationRight = 0;
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
void updateArrowElements(Arrow &arrow)
{
    const float maxRadius = 50;
    RadiusL = std ::min(RadiusL, maxRadius);
    RadiusR = std ::min(RadiusR, maxRadius);
    const sf::Vector2f headOffset = toEuclidean(RadiusL, arrow.rotationLeft);
    arrow.ellipseLeft.setPosition(arrow.ellipseLeftPosition + headOffset);
    const sf::Vector2f headOffset2 = toEuclidean(RadiusR, arrow.rotationRight);
    arrow.ellipseRight.setPosition(arrow.ellipseRightPosition + headOffset2);
    arrow.ellipseRight.setRotation(toDegrees(0));
    arrow.ellipseLeft.setRotation(toDegrees(0));
    arrow.ellipseLeftFon.setPosition(arrow.ellipseLeftFonPosition);
    arrow.ellipseRightFon.setPosition(arrow.ellipseRightFonPosition);
    //   const sf::Vector2f ctemOffset = toEuclidean(50, arrow.rotation);
    //   arrow.ellipseInternal.setPosition(arrow.position);
    //  arrow.ellipseInternal.setRotation(toDegrees(arrow.rotation));
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}
// Инициализирует фигуру-стрелку

void initArrow(Arrow &arrow)
{
    constexpr int pointCount = 200;

    const sf::Vector2f ellipseRightFonRadius = {75.f, 150.f};
    arrow.ellipseRightFonPosition = {500, 300};
    arrow.ellipseRightFon.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    arrow.ellipseRightFon.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRightFonRadius.x * std::sin(angle),
            ellipseRightFonRadius.y * std::cos(angle)};
        arrow.ellipseRightFon.setPoint(pointNo, point);
    }

    const sf::Vector2f ellipseLeftFonRadius = {75.f, 150.f};
    arrow.ellipseLeftFonPosition = {300, 300};
    arrow.ellipseLeftFon.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    arrow.ellipseLeftFon.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseLeftFonRadius.x * std::sin(angle),
            ellipseLeftFonRadius.y * std::cos(angle)};
        arrow.ellipseLeftFon.setPoint(pointNo, point);
    }

    const sf::Vector2f ellipseRightRadius = {20.f, 40.f};
    arrow.ellipseRightPosition = {300, 300};
    arrow.ellipseRight.setFillColor(sf::Color(0xFF, 0, 0));
    arrow.ellipseRight.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRightRadius.x * std::sin(angle),
            ellipseRightRadius.y * std::cos(angle)};
        arrow.ellipseRight.setPoint(pointNo, point);
    }

    const sf::Vector2f ellipseLeftRadius = {20.f, 40.f};
    arrow.ellipseLeftPosition = {500, 300};
    arrow.ellipseLeft.setFillColor(sf::Color(0xFF, 0, 0));
    arrow.ellipseLeft.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseLeftRadius.x * std::sin(angle),
            ellipseLeftRadius.y * std::cos(angle)};
        arrow.ellipseLeft.setPoint(pointNo, point);
    }

    updateArrowElements(arrow);
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
void update(const sf::Vector2f &mousePosition, Arrow &arrow)
{
    const sf::Vector2f delta = mousePosition - arrow.ellipseLeftPosition;
    arrow.rotationLeft = atan2(delta.y, delta.x);
    RadiusL = delta.x * delta.x + delta.y * delta.y;
    RadiusL = sqrt(RadiusL);
    const sf::Vector2f delta2 = mousePosition - arrow.ellipseRightPosition;
    arrow.rotationRight = atan2(delta2.y, delta2.x);
    RadiusR = delta2.x * delta2.x + delta2.y * delta2.y;
    RadiusR = sqrt(RadiusR);
    updateArrowElements(arrow);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Arrow &arrow)
{
    window.clear();
    window.draw(arrow.ellipseLeftFon);
    window.draw(arrow.ellipseRightFon);
    window.draw(arrow.ellipseLeft);
    window.draw(arrow.ellipseRight);
    window.display();
    //  window.draw(arrow.ellipseInternal);
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    Arrow arrow;

    sf::Vector2f mousePosition;

    initArrow(arrow);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, arrow);
        redrawFrame(window, arrow);
    }
}