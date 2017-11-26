#include "stdafx.h"
#include "Knight.h"

bool Knight::isValidMove(int newX, int newY, Color owner)
{
	// TODO implement
	return false;
}

std::string Knight::toString()
{
	return "Knight (" + getColorString() + ") " + getPositonString();
}

std::string Knight::toShortString()
{
	return (getColor() == WHITE) ? "N" : "n";
}