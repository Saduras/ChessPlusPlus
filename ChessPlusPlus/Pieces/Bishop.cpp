#include "stdafx.h"
#include "Bishop.h"
#include "Board.h"

static Position offsets[4]{
	Position{ 1, 1 },
	Position{ 1, -1 },
	Position{ -1, -1 },
	Position{ -1, 1 }
};

std::vector<Position> getMoves(Bishop *self, Position pos, Board &board, bool includingThreats)
{
	std::vector<Position> fields{};

	int directionCount = sizeof(offsets) / sizeof(offsets[0]);
	for (int i = 0; i < directionCount; i++)
	{
		auto newPos = pos + offsets[i];
		while (Position::isOnBoard(newPos))
		{
			auto other = board.getPieceAt(newPos);
			if (other)
			{
				if(includingThreats || other->getColor() != self->getColor())
					fields.push_back(newPos);
				break;
			}
			else
			{
				fields.push_back(newPos);
				newPos += offsets[i];
			}
		}
	}

	return fields;
}

std::vector<Position> Bishop::getMovesFor(Position pos, Board &board)
{
	return getMoves(this, pos, board, false);
}

std::vector<Position> Bishop::getThreatedFieldsFor(Position pos, Board &board)
{
	return getMoves(this, pos, board, true);
}

std::string Bishop::toString()
{
	return "Bishop (" + getColorString() + ")";
}

std::string Bishop::toShortString()
{
	return (getColor() == WHITE) ? "B" : "b";
}