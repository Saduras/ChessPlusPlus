#pragma once

#include "stdafx.h"
#include "Pieces.h"
#include "Position.h"
#include <array>

class Board
{
public:
	 Board();
	~Board();

	Piece* getPieceAt(Position pos);
	void placePieceAt(Piece *const piece, Position pos);
	bool movePiece(Position fromPos, Position toPos);

private:
	static std::array<Piece*, 64> fields;

	int getFieldIndex(Position pos);
};