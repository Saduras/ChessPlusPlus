#include "stdafx.h"
#include "King.h"

static Position offsets[8]{
	Position{ 1, 0},
	Position{ 1, -1 },
	Position{ 0, -1 },
	Position{ -1, -1 },
	Position{ -1, 0 },
	Position{ -1, 1 },
	Position{ 0, 1 },
	Position{ 1, 1 }
};

std::vector<Position> King::getMovesFor(Position startPos)
{
	std::vector<Position> vector{};

	for (int i = 0; i < 8; i++)
	{
		auto newPos = Position{ startPos.x + offsets[i].x, startPos.y + offsets[i].y };
		if (Position::isOnBoard(newPos))
			vector.push_back(newPos);
	}

	return vector;
}

std::string King::toString()
{
	return "King (" + getColorString() + ")";
}

std::string King::toShortString()
{
	return (getColor() == WHITE) ? "K" : "k";
}