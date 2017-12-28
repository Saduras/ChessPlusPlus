#include "stdafx.h"
#include "Position.h"

bool Position::isOnBoard(Position pos)
{
	return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;;
}

