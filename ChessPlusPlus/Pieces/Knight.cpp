#include "stdafx.h"
#include "Knight.h"
#include "Board.h"

static Position offsets[8]{
	Position{ 2, 1 },
	Position{ 2, -1 },
	Position{ 1, -2 },
	Position{ -1, -2 },
	Position{ -2, -1 },
	Position{ -2, 1 },
	Position{ -1, 2 },
	Position{ 1, 2 }
};

std::vector<Position> getMoves(Knight* self, Position startPos, Board &board, bool includeThreats)
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

std::vector<Position> Knight::getMovesFor(Position startPos, Board &board)
{
	return getMoves(this, startPos, board, false);
}

std::vector<Position> Knight::getThreatedFieldsFor(Position startPos, Board &board)
{
	return getMoves(this, startPos, board, true);
}

Piece* Knight::clone()
{
	return new Knight{ this->getColor() };
}

std::string Knight::toString()
{
	return "Knight (" + getColorString() + ")";
}

std::string Knight::toShortString()
{
	return (getColor() == WHITE) ? "N" : "n";
}