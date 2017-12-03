#include "stdafx.h"
#include "Bishop.h"

std::vector<Position> Bishop::getMovesFor(Position startPos)
{
	std::vector<Position> vector{};

	for (int x = startPos.x + 1, y = startPos.y + 1;
		x < 8 && y < 8;
		x++, y++)
	{
		vector.push_back(Position{ x, y });
	}

	for (int x = startPos.x + 1, y = startPos.y - 1;
		x < 8 && y >= 0;
		x++, y--)
	{
		vector.push_back(Position{ x, y });
	}

	for (int x = startPos.x - 1, y = startPos.y - 1;
		x >= 0 && y >= 0;
		x--, y--)
	{
		vector.push_back(Position{ x, y });
	}

	for (int x = startPos.x - 1, y = startPos.y + 1;
		x >= 0 && y < 8;
		x--, y++)
	{
		vector.push_back(Position{ x, y });
	}

	return vector;
}

std::string Bishop::toString()
{
	return "Bishop (" + getColorString() + ")";
}

std::string Bishop::toShortString()
{
	return (getColor() == WHITE) ? "B" : "b";
}