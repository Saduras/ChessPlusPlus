#pragma once

#include <string>

struct Position
{
	int x;
	int y;

	static bool isOnBoard(Position pos);
	static std::string toString(Position pos);

	struct Position& operator+=(const Position& rhs) { x += rhs.x; y += rhs.y; return *this; }
	struct Position& operator-=(const Position& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
};

inline bool operator==(const Position& lhs, const Position& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!=(const Position& lhs, const Position& rhs) { return !(lhs == rhs); }
inline Position operator+(const Position& lhs, const Position& rhs) { return Position{ lhs.x + rhs.x, lhs.y + rhs.y }; }
inline Position operator-(const Position& lhs, const Position& rhs) { return Position{ lhs.x - rhs.x, lhs.y - rhs.y }; }
