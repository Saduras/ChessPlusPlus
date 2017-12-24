#include "stdafx.h"
#include "Piece.h"

Piece::Piece(Color col)
{
	color = col;
}

bool Piece::isValidMove(Move move, Board &board)
{
	auto moves = getMovesFor(move.from, board);

	for (unsigned int i = 0; i < moves.size(); i++)
	{
		if (moves[i] == move.to)
			return true;
	}

	return false;
}