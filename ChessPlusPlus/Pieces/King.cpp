#include "stdafx.h"
#include "King.h"
#include "Board.h"

static Position offsets[8]{
	Position{ 1, 0 },
	Position{ 1, -1 },
	Position{ 0, -1 },
	Position{ -1, -1 },
	Position{ -1, 0 },
	Position{ -1, 1 },
	Position{ 0, 1 },
	Position{ 1, 1 }
};

std::vector<Position> getMoves(King* self, Position startPos, Board &board, bool includeThreats)
{
	std::vector<Position> fields{};

	for (int i = 0; i < 8; i++)
	{
		auto newPos = Position{ startPos.x + offsets[i].x, startPos.y + offsets[i].y };

		if (Position::isOnBoard(newPos))
		{
			auto targetPiece = board.getPieceAt(newPos);
			if (targetPiece == nullptr || includeThreats || targetPiece->getColor() != self->getColor())
			{
				fields.push_back(newPos);
			}
		}
	}

	return fields;
}

std::vector<Position> King::getMovesFor(Position startPos, Board &board)
{
	return getMoves(this, startPos, board, false);
}

std::vector<Position> King::getThreatedFieldsFor(Position startPos, Board &board)
{
	return getMoves(this, startPos, board, true);
}

std::string King::toString()
{
	return "King (" + getColorString() + ")";
}

std::string King::toShortString()
{
	return (getColor() == WHITE) ? "K" : "k";
}