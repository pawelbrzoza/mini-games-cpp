#pragma once

#include <random>

const short SNAKE_SPEED = 200; // sleep time [ms]
const short BOARD_HEIGHT = 15;
const short BOARD_WIDTH = 15;

struct Point
{
	short x, y;

	const bool operator==(const Point& point)
	{
		if (point.x == x && point.y == y)
		{
			return true;
		}
		return false;
	}
};

enum Direction { UP, DOWN, RIGHT, LEFT, UNKNOWN };

int getRandomNum(const int& from, const int& to)
{
	std::random_device rd;
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> dist(from, to);
	return dist(rnd);
}

void clearConsole()
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}
