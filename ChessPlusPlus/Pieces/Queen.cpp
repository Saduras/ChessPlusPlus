#include "stdafx.h"
#include "Queen.h"
#include "Board.h"

static Position offsets[8]{
	// straigth lines
	Position{ 1, 0 },
	Position{ 0, -1 },
	Position{ 1, -0 },
	Position{ 0, 1 },
	// diagonales
	Position{ 1, 1 },
	Position{ 1, -1 },
	Position{ -1, -1 },
	Position{ -1, 1 }
};

std::vector<Position> Queen::getMovesFor(Position pos, Board &board)
{
	std::vector<Position> vector{};

	int directionCount = sizeof(offsets) / sizeof(offsets[0]);
	for (int i = 0; i < directionCount; i++)
	{
		auto newPos = pos + offsets[i];
		while (Position::isOnBoard(newPos))
		{
			auto other = board.getPieceAt(newPos);
			if (other)
			{
				if (other->getColor() == this->getColor())
					vector.push_back(newPos);

				break;
			}
			else
			{
				vector.push_back(newPos);
				newPos += offsets[i];
			}
		}
	}

	return vector;
}

std::string Queen::toString()
{
	return "King (" + getColorString() + ")";
}

std::string Queen::toShortString()
{
	return (getColor() == WHITE) ? "Q" : "q";
}