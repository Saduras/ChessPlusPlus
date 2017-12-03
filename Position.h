#pragma once

#include <string>

struct Position
{
	int x;
	int y;

	static bool isOnBoard(Position pos);
	static std::string toString(Position pos);
};