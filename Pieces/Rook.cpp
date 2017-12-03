#include "stdafx.h"
#include "Rook.h"

std::vector<Position> Rook::getMovesFor(Position startPos)
{
	std::vector<Position> vector{};

	for (int x = startPos.x + 1; x < 8; x++)
		vector.push_back( Position{ x, startPos.y } );

	for (int x = startPos.x - 1; x >= 0; x--)
		vector.push_back(Position{ x, startPos.y });

	for (int y = startPos.y + 1; y < 8; y++)
		vector.push_back(Position{ startPos.x, y });

	for (int y = startPos.y - 1; y >= 0; y--)
		vector.push_back(Position{ startPos.x, y });

	return vector;
}

std::string Rook::toString()
{
	return "King (" + getColorString() + ")";
}

std::string Rook::toShortString()
{
	return (getColor() == WHITE) ? "R" : "r";
}