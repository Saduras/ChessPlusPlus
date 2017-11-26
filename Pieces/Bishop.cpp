#include "stdafx.h"
#include "Bishop.h"

bool Bishop::isValidMove(int newX, int newY, Color owner)
{
	// TODO implement
	return false;
}

std::string Bishop::toString()
{
	return "Bishop (" + getColorString() + ") " + getPositonString();
}

std::string Bishop::toShortString()
{
	return (getColor() == white) ? "B" : "b";
}