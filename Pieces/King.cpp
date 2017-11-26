#include "stdafx.h"
#include "King.h"

bool King::isValidMove(int newX, int newY, Color owner)
{
	// TODO implement
	return false;
}

std::string King::toString()
{
	return "King (" + getColorString() + ") " + getPositonString();
}

std::string King::toShortString()
{
	return (getColor() == white) ? "K" : "k";
}