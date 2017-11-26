#include "stdafx.h"
#include "Queen.h"

bool Queen::isValidMove(int newX, int newY, Color owner)
{
	// TODO implement
	return false;
}

std::string Queen::toString()
{
	return "King (" + getColorString() + ") " + getPositonString();
}

std::string Queen::toShortString()
{
	return (getColor() == white) ? "Q" : "q";
}