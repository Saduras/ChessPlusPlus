#include "stdafx.h"
#include "Pawn.h"

std::vector<Position> Pawn::getMovesFor(Position startPos)
{
	if (getColor() == Color::WHITE)
		return std::vector<Position>{ Position{ startPos.x, startPos.y + 1 } };
	else
		return std::vector<Position>{ Position{ startPos.x + 1, startPos.y } };
}

std::string Pawn::toString()
{
	return "Pawn (" + getColorString() + ") ";
}

std::string Pawn::toShortString()
{
	return (getColor() == WHITE) ? "P" : "p";
}
