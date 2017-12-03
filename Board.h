#pragma once

#include "stdafx.h"
#include "Position.h"
#include "Pieces.h"
#include <array>

class Board
{
public:
	Board();
	~Board();

	Piece* getPieceAt(Position pos);
	void placePieceAt(Piece *const piece, Position pos);
	bool isValidMove(Position from, Position to);
	void movePiece(Position from, Position to);

private:
	static std::array<Piece*, 64> fields;

	int getFieldIndex(Position pos);
};