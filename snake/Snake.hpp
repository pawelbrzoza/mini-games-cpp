#pragma once

#include "Common.hpp"

class Snake
{
	std::vector<std::tuple<Point, Direction>> curvePoints;
	std::vector<std::tuple<Point, Direction>> snakePoints;

public:

	Snake()
	{
		Point head;
		head.x = getRandomNum(1, BOARD_HEIGHT - 2);
		head.y = getRandomNum(1, BOARD_WIDTH - 2);
		snakePoints.push_back(std::make_tuple(head, Direction::UNKNOWN));
	}

	std::vector<std::tuple<Point, Direction>>& getSnakePoints()
	{
		return snakePoints;
	}

	void updateSnakeDirection()
	{
		auto& direction = std::get<1>(snakePoints.front());
		if ((GetKeyState(VK_UP) & 0x8000) && direction != Direction::UP
			&& direction != Direction::DOWN)
		{
			direction = Direction::UP;
			curvePoints.push_back(snakePoints.front());
		}
		else if ((GetKeyState(VK_DOWN) & 0x8000) && direction != Direction::DOWN
			&& direction != Direction::UP)
		{
			direction = Direction::DOWN;
			curvePoints.push_back(snakePoints.front());
		}
		else if ((GetKeyState(VK_RIGHT) & 0x8000) && direction != Direction::RIGHT
			&& direction != Direction::LEFT)
		{
			direction = Direction::RIGHT;
			curvePoints.push_back(snakePoints.front());
		}
		else if ((GetKeyState(VK_LEFT) & 0x8000) && direction != Direction::LEFT
			&& direction != Direction::RIGHT)
		{
			direction = Direction::LEFT;
			curvePoints.push_back(snakePoints.front());
		}
	}

	void shiftSnake()
	{
		for (auto&& el : snakePoints)
		{
			auto& point = std::get<0>(el);
			auto& direction = std::get<1>(el);

			for (const auto& cur : curvePoints)
			{
				const auto& pCurve = std::get<0>(cur);
				const auto& dCurve = std::get<1>(cur);
				if (point == pCurve)
				{
					direction = dCurve;
					break;
				}
			}

			if (direction == Direction::UP)
			{
				point.x--;
			}
			else if (direction == Direction::DOWN)
			{
				point.x++;
			}
			else if (direction == Direction::RIGHT)
			{
				point.y++;
			}
			else if (direction == Direction::LEFT)
			{
				point.y--;
			}
		}

		if (!curvePoints.empty())
		{
			bool toDel = true;
			for (auto&& el : snakePoints)
			{
				auto& point = std::get<0>(el);
				const auto& firstCurve = std::get<0>(curvePoints.front());
				if (point == firstCurve)
				{
					toDel = false;
				}
			}
			if (toDel)
			{
				curvePoints.erase(curvePoints.begin());
			}
		}
	}

	void eatSeed(Point& seed)
	{
		auto& head = std::get<0>(snakePoints.front());
		auto tail = std::get<0>(snakePoints.back());
		if (head == seed)
		{
			const auto& direction = std::get<1>(snakePoints.back());
			if (direction == Direction::UP)
			{
				tail.x++;
			}
			else if (direction == Direction::DOWN)
			{
				tail.x--;
			}
			else if (direction == Direction::RIGHT)
			{
				tail.y--;
			}
			else if (direction == Direction::LEFT)
			{
				tail.y++;
			}
			snakePoints.push_back(std::make_tuple(tail, direction));
			seed.x = seed.y = -1;
		}
	}

	bool boundValidation()
	{
		bool valid = true;
		auto& head = std::get<0>(snakePoints.front());

		// boundaries
		for (size_t i = 0; i < BOARD_WIDTH; i++)
		{
			if (head.x == 0 && head.y == i)
			{
				valid = false;
				break;
			}
			if (head.x == BOARD_HEIGHT - 1 && head.y == i)
			{
				valid = false;
				break;
			}
		}

		for (size_t i = 0; i < BOARD_HEIGHT; i++)
		{
			if (head.x == i && head.y == 0)
			{
				valid = false;
				break;
			}
			if (head.x == i && head.y == BOARD_WIDTH - 1)
			{
				valid = false;
				break;
			}
		}

		// snake
		if (snakePoints.size() > 1)
		{
			for (auto it = snakePoints.begin() + 1; it != snakePoints.end(); ++it)
			{
				const auto& body = std::get<0>(*it);
				if (head == body)
				{
					valid = false;
				}
			}
		}

		return valid;
	}
};