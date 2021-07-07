#pragma once

#include <SFML/Graphics.hpp>

const float BRICK_WIDTH = 80;
const float BRICK_HEIGHT = 30;

class Brick
{
public:
    sf::RectangleShape brickShape;
    bool               destroyed = false;

    Brick(float x, float y)
    {
        brickShape.setPosition(x, y);
        brickShape.setSize({BRICK_WIDTH, BRICK_HEIGHT});
        brickShape.setFillColor(sf::Color::Yellow);
        brickShape.setOrigin(BRICK_WIDTH / 2, BRICK_HEIGHT / 2);
    }

    float x() { return brickShape.getPosition().x; }
    float y() { return brickShape.getPosition().y; }
    float left() { return x() - brickShape.getSize().x / 2; }
    float right() { return x() + brickShape.getSize().x / 2; }
    float top() { return y() - brickShape.getSize().y / 2; }
    float bottom() { return y() + brickShape.getSize().y / 2; }
};