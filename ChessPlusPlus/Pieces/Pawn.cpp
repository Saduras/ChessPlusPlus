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

int getStartY(Color color)
{
	return color == Color::WHITE ? 1 : 6;
}

Position getMoveDir(Color color)
{
	return color == Color::WHITE ? moveDirs[0] : moveDirs[1];
}

void addAttackMoves(Pawn* self, Position pos, Position moveDir, Board &board, bool includeThreads, std::vector<Position> &moves)
{
	for (int i = 0; i < 2; i++)
	{
		Position newPos = pos + moveDir + attackDirOffsets[i];

		if (Position::isOnBoard(newPos))
		{
			auto targetPiece = board.getPieceAt(newPos);
			if (targetPiece && (includeThreads || targetPiece->getColor() != self->getColor()))
				moves.push_back(newPos);
		}
	}
}

std::vector<Position> Pawn::getMovesFor(Position pos, Board &board)
{
	std::vector<Position> moves{};

	Position moveDir = getMoveDir(getColor());
	int startY = getStartY(getColor());

	// normal move
	auto newPos = pos + moveDir;
	if(Position::isOnBoard(newPos) && !board.getPieceAt(newPos))
		moves.push_back(newPos);

	// start move
	newPos = pos + moveDir + moveDir;
	if (pos.y == startY && Position::isOnBoard(newPos) && !board.getPieceAt(newPos))
		moves.push_back(newPos);
	
	// attack moves
	addAttackMoves(this, pos, moveDir, board, false, moves);

	return moves;
}

std::vector<Position> Pawn::getThreatedFieldsFor(Position pos, Board &board)
{
	std::vector<Position> moves{};

	Position moveDir = getMoveDir(getColor());
	addAttackMoves(this, pos, moveDir, board, true, moves);

	return moves;
}

Piece* Pawn::clone()
{
	return new Pawn{ this->getColor() };
}

std::string Pawn::toString()
{
	return "Pawn (" + getColorString() + ") ";
}

std::string Pawn::toShortString()
{
	return (getColor() == WHITE) ? "P" : "p";
}
