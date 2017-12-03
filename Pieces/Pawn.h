#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	using Piece::Piece;

	std::vector<Position> getMovesFor(Position startPos);

	std::string toString();
	std::string toShortString();
};