#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Ball.hpp"
#include "Brick.hpp"
#include "ErrorFile.hpp"
#include "GameState.hpp"
#include "Paddle.hpp"
#include "TestCollision.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>

class Level
{
public:
    Level();
    Level(int currLevel);

    virtual GameState run() = 0;

    virtual ~Level();

protected:
    std::vector<Brick>                bricks;
    int                               currentLevel;
    virtual void                      createBricks() = 0;
    GameState                         runEngine();

private:
    Ball       ball;
    Paddle     paddle;
    sf::Text   textLives;
    sf::Text   textPoints;
    sf::Text   textBoxPoints;
    sf::Text   textBoxLives;
    sf::Event  event;
    //Clock FPSClock;

    void drawLevelInfo();

    void drawLevelEnd(const std::string mainText);

    void drawElementsAndCheckBricks();
};
