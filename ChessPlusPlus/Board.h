#pragma once

#include "stdafx.h"
#include "Position.h"
#include "Pieces.h"
#include <array>

class Board
{
public:
	~Board();

	void setupWithDefault();

	Piece* getPieceAt(Position pos);
	void placePieceAt(Piece *const piece, Position pos);

	bool isValidMove(Position from, Position to, Color playerColor);
	bool isThreatenedBy(Position targetPos, Color playerColor);

	void movePiece(Position from, Position to);
	void removePieceAt(Position pos);

	void clear();

private:
	std::array<Piece*, 64> fields{};

	int getFieldIndex(Position pos);
};