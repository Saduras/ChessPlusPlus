#include "stdafx.h"
#include "Piece.h"

Piece::Piece(Color col)
{
	color = col;
}

bool Piece::isValidMove(Position from, Position to, Board &board)
{
	auto moves = getMovesFor(from, board);

	for (unsigned int i = 0; i < moves.size(); i++)
	{
		if (moves[i] == to)
			return true;
	}

	return false;
}