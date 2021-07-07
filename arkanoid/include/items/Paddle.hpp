#pragma once

#include "Common.hpp"
#include "GameSettings.hpp"

#include <SFML/Graphics.hpp>

const float PADDLE_WIDTH = 150;
const float PADDLE_HEIGHT = 20;
const float PADDLE_VELOCITY = 12;

class Paddle
{
public:
    sf::RectangleShape paddleShape;
    sf::Vector2f       paddleVelocity;
    int                lastMouseX;

    Paddle() {}
    Paddle(float x, float y)
    {
        paddleShape.setPosition(x, y);
        paddleShape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
        paddleShape.setFillColor(sf::Color::Black);
        paddleShape.setOrigin(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2);

        sf::Vector2i winPos(x, y);
        sf::Mouse::setPosition(winPos, *window);
    }

    void updatePosition()
    {
        if (GameParam::isMouseControl == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0)
                paddleVelocity.x = -PADDLE_VELOCITY;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < WINDOW_WIDTH)
                paddleVelocity.x = PADDLE_VELOCITY;
            else
                paddleVelocity.x = 0;

            paddleShape.move(paddleVelocity);
        }
        else
        {
            // int currMouseX = sf::Mouse::getPosition(*window).x;
            // if (currMouseX - paddleShape.getSize().x / 2 > 0 && currMouseX + paddleShape.getSize().x / 2 < WINDOW_WIDTH)
            // {
            //     paddleShape.setPosition(currMouseX, WINDOW_HEIGHT - 50);
            // }

            int currMouseX = sf::Mouse::getPosition(*window).x;

            if (currMouseX > lastMouseX && right() < WINDOW_WIDTH)
            {
                paddleVelocity.x = PADDLE_VELOCITY;
            }
            else if (currMouseX < lastMouseX && left() > 0)
            {
                paddleVelocity.x = -PADDLE_VELOCITY;
            }
            else
            {
                paddleVelocity.x = 0;
            }

            // sf::Vector2i winPos(x(), y());
            // sf::Mouse::setPosition(winPos, *window);

            paddleShape.move(paddleVelocity);

            lastMouseX = currMouseX;
        }
    }

    float x() { return paddleShape.getPosition().x; }
    float y() { return paddleShape.getPosition().y; }
    float left() { return x() - paddleShape.getSize().x / 2; }
    float right() { return x() + paddleShape.getSize().x / 2; }
    float top() { return y() - paddleShape.getSize().y / 2; }
    float bottom() { return y() + paddleShape.getSize().y / 2; }
};
