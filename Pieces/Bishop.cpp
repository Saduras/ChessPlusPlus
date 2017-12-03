#include "stdafx.h"
#include "Bishop.h"
#include "Board.h"

static Position offsets[4]{
	Position{ 1, 1 },
	Position{ 1, -1 },
	Position{ -1, -1 },
	Position{ -1, 1 }
};

std::vector<Position> Bishop::getMovesFor(Position pos, Board &board)
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

std::string Bishop::toString()
{
	return "Bishop (" + getColorString() + ")";
}

std::string Bishop::toShortString()
{
	return (getColor() == WHITE) ? "B" : "b";
}