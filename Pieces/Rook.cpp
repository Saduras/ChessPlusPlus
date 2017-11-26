#include "stdafx.h"
#include "Rook.h"

bool Rook::isValidMove(int newX, int newY, Color owner)
{
	// TODO implement
	return false;
}

std::string Rook::toString()
{
	return "King (" + getColorString() + ") " + getPositonString();
}

std::string Rook::toShortString()
{
	return (getColor() == WHITE) ? "R" : "r";
}