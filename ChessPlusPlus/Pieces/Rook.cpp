#include "stdafx.h"
#include "Rook.h"
#include "Board.h"

static Position offsets[4]{
	Position{ 1, 0 },
	Position{ 0, -1 },
	Position{ -1, 0 },
	Position{ 0, 1 }
};

std::vector<Position> getMoves(Rook* self, Position pos, Board &board, bool includeThreats)
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
				if (includeThreats || other->getColor() != self->getColor())
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

std::vector<Position> Rook::getMovesFor(Position pos, Board &board)
{
	return getMoves(this, pos, board, false);
}

std::vector<Position> Rook::getThreatedFieldsFor(Position pos, Board &board)
{
	return getMoves(this, pos, board, true);
}

std::string Rook::toString()
{
	return "King (" + getColorString() + ")";
}

std::string Rook::toShortString()
{
	return (getColor() == WHITE) ? "R" : "r";
}