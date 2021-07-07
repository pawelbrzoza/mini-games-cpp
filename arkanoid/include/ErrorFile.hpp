#pragma once

#include <memory>

#include "Common.hpp"
#include "GameSettings.hpp"
#include "Error.hpp"

#include <SFML/Graphics.hpp>

class ErrorFile : public Error
{
public:
    virtual void error(const std::string errorMsg = "PROBLEM WITH FILE...")
    {
        sf::Text game_over(errorMsg, GameParam::font, 40);
        game_over.setPosition(WINDOW_WIDTH / 2 - game_over.getGlobalBounds().width / 2,
                              WINDOW_HEIGHT / 2 - game_over.getGlobalBounds().height / 2);
        game_over.setFillColor(sf::Color::White);
        window->clear(sf::Color::Blue);
        window->draw(game_over);
        window->display();
        sf::sleep(sf::milliseconds(WAIT_5_SEC));
        exit(0);
    }
};