#include "Game.hpp"

Game::Game() : gameState(GameState::MENU)
{
    // window->setMouseCursorGrabbed(true);
}

void Game::start()
{
    while (gameState != GameState::END)
    {
        switch (gameState)
        {
        case GameState::MENU:
            window->setMouseCursorVisible(true);
            gameState = menu->menu();
            break;
        case GameState::NEWGAME:
            // window->setMouseCursorVisible(false);
            gameState = menu->play();
            break;
        case GameState::OPTIONS:
            gameState = menu->options();
            break;
        }
    }
}
