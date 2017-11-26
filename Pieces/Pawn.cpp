#include "stdafx.h"
#include "Pawn.h"

bool Pawn::isValidMove(int newX, int newY, Color owner)
{
	if (!isOnBoard(newX, newY))
	{
		return false;
	}

	int direction = getColor() == WHITE ? 1 : -1;
	Color opponent = getColor() == WHITE ? BLACK : WHITE;
	int x = getPosition()[0];
	int y = getPosition()[1];

	return newY == y + direction
		&& (newX == x || (abs(newX - x) == 1 && owner == opponent));
}

std::string Pawn::toString()
{
	return "Pawn (" + getColorString() + ") " + getPositonString();
}

std::string Pawn::toShortString()
{
	return (getColor() == WHITE) ? "P" : "p";
}
