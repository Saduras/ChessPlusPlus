#include "stdafx.h"
#include "Pawn.h"
#include "Board.h"

static Position moveDirs[2]
{
	Position{0, 1},
	Position{0, -1},
};

static Position attackDirOffsets[2]
{
	Position{1, 0},
	Position{-1, 0}
};

std::vector<Position> Pawn::getMovesFor(Position pos, Board &board)
{
	std::vector<Position> vector{};

	Position moveDir;
	int startY;
	if (getColor() == Color::WHITE)
	{
		moveDir = moveDirs[0];
		startY = 1;
	}
	else
	{
		moveDir = moveDirs[1];
		startY = 6;
	}

	// normal move
	auto newPos = pos + moveDir;
	if(Position::isOnBoard(newPos) && !board.getPieceAt(newPos))
		vector.push_back(newPos);

	// start move
	newPos = pos + moveDir + moveDir;
	if (pos.y == startY && Position::isOnBoard(newPos) && !board.getPieceAt(newPos))
		vector.push_back(newPos);
	
	// attack moves
	for (int i = 0; i < 2; i++)
	{
		newPos = pos + moveDir + attackDirOffsets[i];

		if (Position::isOnBoard(newPos))
		{
			auto targetPiece = board.getPieceAt(newPos);
			if (targetPiece && targetPiece->getColor() != this->getColor())
				vector.push_back(newPos);
		}
	}

	return vector;
}

std::string Pawn::toString()
{
	return "Pawn (" + getColorString() + ") ";
}

std::string Pawn::toShortString()
{
	return (getColor() == WHITE) ? "P" : "p";
}
