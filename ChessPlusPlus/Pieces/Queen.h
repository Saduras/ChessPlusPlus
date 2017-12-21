#pragma once

#include "Piece.h"
#include <string>

class Queen : public Piece
{
public:
	using Piece::Piece;

	std::vector<Position> getMovesFor(Position startPos, Board &board);
	std::vector<Position> getThreatedFieldsFor(Position startPos, Board &board);

	std::string toString();
	std::string toShortString();
};