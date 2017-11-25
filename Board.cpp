#include "stdafx.h"
#include "Board.h"

// public
Piece* Board::getPieceAt(int x, int y)
{
	return fields.at(getFieldIndex(x, y));
}

void Board::placePieceAt(Piece *const piece, int x, int y)
{
	fields[getFieldIndex(x, y)] = piece;
}

// private
std::array<Piece*, 64> Board::fields{};

int Board::getFieldIndex(int x, int y)
{
	return x + y * 8;
}
