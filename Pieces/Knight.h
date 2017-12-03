#pragma once

#include "Piece.h"
#include <string>

class Knight : public Piece
{
public:
	using Piece::Piece;

	std::vector<Position> getMovesFor(Position startPos, Board &board);

	std::string toString();
	std::string toShortString();
};