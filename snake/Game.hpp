#pragma once

#include <tuple>

#include "Board.hpp"
#include "Snake.hpp"

class Game
{
	Snake snake;
	Board board;

public:
	void lunchGame()
	{
		while (true)
		{
			// manage snake
			board.putSeed(snake.getSnakePoints());
			snake.eatSeed(board.getSeed());
			snake.updateSnakeDirection();
			snake.shiftSnake();

			// validation
			if (!snake.boundValidation())
			{
				std::cout << "GAME OVER\n";
				break;
			}

			// print
			board.clearBoard();
			for (auto&& el : snake.getSnakePoints())
			{
				board.assignSnakePoint(std::get<0>(el));
			}
			board.printBoard();

			// exit
			if (GetKeyState(VK_ESCAPE) & 0x8000)
			{
				break;
			}
			// wait
			Sleep(SNAKE_SPEED);
		}
	}
};
