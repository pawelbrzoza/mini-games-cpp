#pragma once

#include <memory>

#include "Common.hpp"
#include "GameMenu.hpp"
#include "GameState.hpp"
#include "GameSettings.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    void start();

private:
    std::unique_ptr<GameMenu> menu = std::make_unique<GameMenu>();
    GameState                 gameState;
};
