#pragma once

#include <Windows.h>
#include <iostream>

#include "Common.hpp"

class Board
{
	//char** board;
	char board[BOARD_HEIGHT][BOARD_WIDTH];
	Point seed;

	void fillBoard()
	{
		for (size_t i = 0; i < BOARD_HEIGHT; i++)
		{
			board[i][0] = '|';
			board[i][BOARD_WIDTH - 1] = '|';
		}
		for (size_t j = 0; j < BOARD_WIDTH; j++)
		{
			board[0][j] = '-';
			board[BOARD_HEIGHT - 1][j] = '-';
		}
		for (size_t i = 1; i < BOARD_HEIGHT - 1; i++)
		{
			for (size_t j = 1; j < BOARD_WIDTH - 1; j++)
			{
				board[i][j] = ' ';
			}
		}
	}

public:

	Board()
	{
		seed.x = -1;
		seed.y = -1;
		//board = new char* [BOARD_HEIGHT];
		//for (size_t i = 0; i < BOARD_HEIGHT; i++)
		//{
		//	board[i] = new char[BOARD_WIDTH];
		//}
		fillBoard();
	}

	Point& getSeed()
	{
		return seed;
	}

	void clearBoard()
	{
		clearConsole();
		for (size_t i = 1; i < BOARD_HEIGHT - 1; i++)
		{
			for (size_t j = 1; j < BOARD_WIDTH - 1; j++)
			{
				if (board[i][j] != '*')
					board[i][j] = ' ';
			}
		}
	}

	void assignSnakePoint(const Point& point)
	{
		board[point.x][point.y] = '@';
	}

	void printBoard()
	{
		std::cout << '\n';
		for (size_t i = 0; i < BOARD_HEIGHT; i++)
		{
			for (size_t j = 0; j < BOARD_WIDTH; j++)
			{
				std::cout << board[i][j] << ' ';
			}
			std::cout << '\n';
		}
		std::cout << "\n Press the Esc button to exit \n";
	}

	void putSeed(const std::vector<std::tuple<Point, Direction>>& snakePoints)
	{
		if (seed.x == -1 && seed.y == -1)
		{
			//int probability = getRandomNum(1, 100);
			//if (probability < 50)
			//{
			bool result;
			do
			{
				result = false;
				seed.x = getRandomNum(1, BOARD_HEIGHT - 2);
				seed.y = getRandomNum(1, BOARD_WIDTH - 2);
				for (auto&& el : snakePoints)
				{
					auto& point = std::get<0>(el);
					if (seed.x == point.x && seed.y == point.y)
					{
						result = true;
						break;
					}
				}
			} while (result);

			board[seed.x][seed.y] = '*';
			//}
		}
	}
};
