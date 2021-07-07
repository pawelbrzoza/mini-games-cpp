#pragma once

#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"

template <class T1, class T2>
bool isIntersecting(T1& t1, T2& t2)
{
    if (t1.right() >= t2.left() && t1.left() <= t2.right() &&
        t1.bottom() >= t2.top() && t1.top() <= t2.bottom())
        return true;
    else
        return false;
}

static void testCollision(Paddle& paddle, Ball& ball)
{
    if (isIntersecting(paddle, ball) == false)
        return;

    ball.ballVelocity.y = -BALL_VELOCITY;

    if (ball.x() < paddle.x() + 1 && ball.x() > paddle.x() - 1)
    {
        ball.ballVelocity.x = 0;
    }
    else if (ball.x() < paddle.x())
    {
        if (ball.x() < paddle.x() - 35)
        {
            ball.ballVelocity.x = -BALL_VELOCITY;
        }
        else if (ball.x() < paddle.x() - 20)
        {
            ball.ballVelocity.x = -(BALL_VELOCITY / 2);
        }
        else if (ball.x() < paddle.x() - 10)
        {
            ball.ballVelocity.x = -(BALL_VELOCITY / 3);
        }
        else if (ball.x() < paddle.x() - 1)
        {
            ball.ballVelocity.x = -(BALL_VELOCITY / 4);
        }
    }
    else
    {
        if (ball.x() > paddle.x() + 35)
        {
            ball.ballVelocity.x = BALL_VELOCITY;
        }
        else if (ball.x() > paddle.x() + 20)
        {
            ball.ballVelocity.x = (BALL_VELOCITY / 2);
        }
        else if (ball.x() > paddle.x() + 10)
        {
            ball.ballVelocity.x = (BALL_VELOCITY / 3);
        }
        else if (ball.x() > paddle.x() + 1)
        {
            ball.ballVelocity.x = (BALL_VELOCITY / 4);
        }
    }
}

static bool testCollision(Brick& brick, Ball& ball)
{
    if (isIntersecting(brick, ball) == false)
        return false;

    brick.destroyed = true;

    float overlapLeft = ball.right() - brick.left();
    float overlapRight = brick.right() - ball.left();
    float overlapTop = ball.bottom() - brick.top();
    float overlapBottom = brick.bottom() - ball.top();

    bool ballFromLeft = abs(overlapLeft) < abs(overlapRight);
    bool ballFromTop = abs(overlapTop) < abs(overlapBottom);

    float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
    float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

    if (abs(minOverlapX) < abs(minOverlapY))
        ball.ballVelocity.x = ballFromLeft ? -BALL_VELOCITY : BALL_VELOCITY;
    else
        ball.ballVelocity.y = ballFromTop ? -BALL_VELOCITY : BALL_VELOCITY;

    return true;
}
