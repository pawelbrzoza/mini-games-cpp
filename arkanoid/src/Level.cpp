#include "Level.hpp"

Level::Level() {}

Level::Level(int currLevel) : currentLevel(currLevel)
{
    paddle = Paddle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50);
    ball = Ball(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 200);

    const size_t charSize = 25;

    textBoxPoints.setString("POINTS: ");
    textBoxPoints.setCharacterSize(charSize);
    textBoxPoints.setFont(GameParam::font);
    textBoxPoints.setPosition(20, WINDOW_HEIGHT - 40);
    textBoxPoints.setFillColor(sf::Color::Black);

    textPoints.setCharacterSize(charSize);
    textPoints.setFont(GameParam::font);
    textPoints.setPosition(140, WINDOW_HEIGHT - 40);
    textPoints.setFillColor(sf::Color::Black);

    textBoxLives.setString("LIVES: ");
    textBoxLives.setCharacterSize(charSize);
    textBoxLives.setFont(GameParam::font);
    textBoxLives.setPosition(WINDOW_WIDTH - 120, WINDOW_HEIGHT - 40);
    textBoxLives.setFillColor(sf::Color::Black);

    textLives.setCharacterSize(charSize);
    textLives.setFont(GameParam::font);
    textLives.setPosition(WINDOW_WIDTH - 30, WINDOW_HEIGHT - 40);
    textLives.setFillColor(sf::Color::Black);

    sf::Text level_num("Level: " + std::to_string(currentLevel), GameParam::font, 60);
    level_num.setPosition(WINDOW_WIDTH / 2 - level_num.getGlobalBounds().width / 2,
                          WINDOW_HEIGHT / 2 - level_num.getGlobalBounds().height / 2);
    level_num.setFillColor(sf::Color::Black);
    window->clear(sf::Color::White);
    window->draw(level_num);
    window->display();

    sf::sleep(sf::milliseconds(WAIT_3_SEC));
}

Level::~Level() {}

GameState Level::runEngine()
{
    while (true)
    {
        window->clear(sf::Color::White);
        window->setFramerateLimit(FRAME_RATE_LIMIT);
        window->pollEvent(event);

        if (event.key.code == sf::Keyboard::Escape)
        {
            return GameState::MENU;
        }

        if (event.type == sf::Event::Closed)
        {
            exit(0);
        }

        if (ball.updatePosition() == true)
        {
            GameParam::lives--;
        }

        if (GameParam::lives <= 0 )
        {
            drawLevelEnd("GAME OVER");
            return GameState::MENU;
        }

        drawElementsAndCheckBricks();

        bricks.erase(remove_if(bricks.begin(), bricks.end(), [](const Brick& mBrick)
                    { return mBrick.destroyed; }), bricks.end());

        paddle.updatePosition();

        testCollision(paddle, ball);

        if (bricks.empty() == true)
        {
            if (currentLevel == NUM_OF_LEVELS)
            {
                drawLevelEnd("YOU WIN !");
                return GameState::MENU;
            }
            drawLevelInfo();
            break;
        }

        window->display();
        //float fps = getFPS(FPSClock.restart());
    }

    return GameState::NEWGAME;
}

void Level::drawLevelInfo()
{
    sf::Text level_num("Level: " + std::to_string(currentLevel + 1), GameParam::font, 60);
    level_num.setPosition(WINDOW_WIDTH / 2 - level_num.getGlobalBounds().width / 2,
                          WINDOW_HEIGHT / 2 - level_num.getGlobalBounds().height / 2);
    level_num.setFillColor(sf::Color::Black);
    window->clear(sf::Color::White);
    window->draw(level_num);
    window->display();
}

void Level::drawLevelEnd(const std::string mainText)
{
    sf::Text level_end(mainText, GameParam::font, 60);
    level_end.setPosition(WINDOW_WIDTH / 2 - level_end.getGlobalBounds().width / 2,
                          WINDOW_HEIGHT / 2 - level_end.getGlobalBounds().height / 2);
    textPoints.setPosition(WINDOW_WIDTH / 2 - level_end.getGlobalBounds().width / 2 + 230,
                           WINDOW_HEIGHT / 2 - level_end.getGlobalBounds().height / 2 + 80);
    textBoxPoints.setPosition(WINDOW_WIDTH / 2 - level_end.getGlobalBounds().width / 2 + 90,
                              WINDOW_HEIGHT / 2 - level_end.getGlobalBounds().height / 2 + 80);
    textPoints.setCharacterSize(30);
    textBoxPoints.setCharacterSize(30);
    level_end.setFillColor(sf::Color::Black);

    window->clear(sf::Color::White);
    window->draw(level_end);
    window->draw(textPoints);
    window->draw(textBoxPoints);
    window->display();
    sf::sleep(sf::milliseconds(WAIT_3_SEC));
}

void Level::drawElementsAndCheckBricks()
{
    window->draw(ball.ballShape);
    window->draw(paddle.paddleShape);

    for (auto& brick : bricks)
    {
        window->draw(brick.brickShape);
        if (testCollision(brick, ball) == true)
            GameParam::points++;
    }

    textLives.setString(std::to_string(GameParam::lives));
    window->draw(textLives);

    textPoints.setString(std::to_string(GameParam::points));
    window->draw(textPoints);

    window->draw(textBoxLives);
    window->draw(textBoxPoints);
}
