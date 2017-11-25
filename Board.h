#pragma once

#include "stdafx.h"
#include "Piece.h"
#include <array>

class Board
{
public:
	Piece* getPieceAt(int x, int y);
	void placePieceAt(Piece *const piece, int x, int y);

private:
	static std::array<Piece*, 64> fields;

	int getFieldIndex(int x, int y);
};