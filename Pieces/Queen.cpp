#include "stdafx.h"
#include "Queen.h"

std::vector<Position> Queen::getMovesFor(Position startPos)
{
	std::vector<Position> vector{};

	// get straight lines
	for (int x = startPos.x + 1; x < 8; x++)
		vector.push_back(Position{ x, startPos.y });

	for (int x = startPos.x - 1; x >= 0; x--)
		vector.push_back(Position{ x, startPos.y });

	for (int y = startPos.y + 1; y < 8; y++)
		vector.push_back(Position{ startPos.x, y });

	for (int y = startPos.y - 1; y >= 0; y--)
		vector.push_back(Position{ startPos.x, y });

	// get diagonales
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

std::string Queen::toString()
{
	return "King (" + getColorString() + ")";
}

std::string Queen::toShortString()
{
	return (getColor() == WHITE) ? "Q" : "q";
}