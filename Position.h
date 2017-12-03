#pragma once

#include <string>

struct Position
{
	int x;
	int y;

	static bool isOnBoard(Position pos);
	static std::string toString(Position pos);

	
};

inline bool operator==(const Position& lhs, const Position& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!=(const Position& lhs, const Position& rhs) { return !(lhs == rhs); }
