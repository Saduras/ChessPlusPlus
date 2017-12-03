#pragma once

#include "Piece.h"
#include <string>

class Queen : public Piece
{
public:
	using Piece::Piece;

	std::vector<Position> getMovesFor(Position startPos);

	std::string toString();
	std::string toShortString();
};