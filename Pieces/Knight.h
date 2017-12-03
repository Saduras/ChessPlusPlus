#pragma once

#include "Piece.h"
#include <string>

class Knight : public Piece
{
public:
	using Piece::Piece;

	std::vector<Position> getMovesFor(Position startPos);

	std::string toString();
	std::string toShortString();
};