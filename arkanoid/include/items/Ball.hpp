#pragma once

#include "Common.hpp"
#include <SFML/Graphics.hpp>

const float BALL_VELOCITY = 7;
const float BALL_RADIUS = 15;

class Ball
{
public:
    sf::CircleShape ballShape;
    sf::Vector2f    ballVelocity{0, BALL_VELOCITY};

    Ball() {}
    Ball(float x, float y)
    {
        ballShape.setPosition(x, y);
        ballShape.setRadius(BALL_RADIUS);
        ballShape.setFillColor(sf::Color::Red);
        ballShape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    }

    bool updatePosition()
    {
        ballShape.move(ballVelocity);

        if (left() < 0)
            ballVelocity.x = BALL_VELOCITY;
        else if (right() > WINDOW_WIDTH)
            ballVelocity.x = -BALL_VELOCITY;

        if (top() < 0)
            ballVelocity.y = BALL_VELOCITY;
        else if (bottom() > WINDOW_HEIGHT)
        {
            ballVelocity.x = 0;
            ballVelocity.y = BALL_VELOCITY / 2;
            ballShape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            return true;
        }

        return false;
    }

    float x() { return ballShape.getPosition().x; }
    float y() { return ballShape.getPosition().y;  }
    float left() { return x() - ballShape.getRadius(); }
    float right() { return x() + ballShape.getRadius(); }
    float top() { return y() - ballShape.getRadius(); }
    float bottom() { return y() + ballShape.getRadius(); }
};
