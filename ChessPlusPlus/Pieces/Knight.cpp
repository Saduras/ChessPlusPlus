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

std::vector<Position> Knight::getMovesFor(Position startPos, Board &board)
{
	std::vector<Position> vector{};

	for (int i = 0; i < 8; i++)
	{
		auto newPos = Position{ startPos.x + offsets[i].x, startPos.y + offsets[i].y };

		if (Position::isOnBoard(newPos))
		{
			auto targetPiece = board.getPieceAt(newPos);
			if (targetPiece == nullptr || targetPiece->getColor() != this->getColor())
			{
				vector.push_back(newPos);
			}
		}
	}

	return vector;
}

std::string Knight::toString()
{
	return "Knight (" + getColorString() + ")";
}

std::string Knight::toShortString()
{
	return (getColor() == WHITE) ? "N" : "n";
}