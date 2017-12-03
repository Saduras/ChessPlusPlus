#include "stdafx.h"
#include "Position.h"

bool Position::isOnBoard(Position pos)
{
	return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;;
}

std::string Position::toString(Position pos)
{
	return std::string(1, (char)((int)'a' + pos.x))
		+ std::to_string(pos.y + 1);
}
