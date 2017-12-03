#pragma once

#include "Piece.h"
#include <string>

class King : public Piece
{
public:
	using Piece::Piece;

	std::vector<Position> getMovesFor(Position startPos);

	std::string toString();
	std::string toShortString();
};