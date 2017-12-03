#include "stdafx.h"
#include "Pawn.h"

std::vector<Position> Pawn::getMovesFor(Position startPos)
{
	std::vector<Position> vector{};

	if (getColor() == Color::WHITE)
	{
		if(startPos.y < 7)
			vector.push_back(Position{ startPos.x, startPos.y + 1 });

		if(startPos.y == 1)
			vector.push_back(Position{ startPos.x, startPos.y + 2 });
	}
	else
	{
		if(startPos.y > 0)
			vector.push_back(Position{ startPos.x, startPos.y - 1 });

		if (startPos.y == 6)
			vector.push_back(Position{ startPos.x, startPos.y - 2 });
	}
	return vector;
}

std::string Pawn::toString()
{
	return "Pawn (" + getColorString() + ") ";
}

std::string Pawn::toShortString()
{
	return (getColor() == WHITE) ? "P" : "p";
}
