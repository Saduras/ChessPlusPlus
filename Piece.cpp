#include "stdafx.h"
#include "Piece.h"

Piece::Piece(int posX, int posY, Color col)
{
	position[0] = posX;
	position[1] = posY;
	color = col;
}

bool Piece::isOnBoard(int posX, int posY)
{
	return -1 < posX && posX < 8
		&& -1 < posY && posY < 8;
}

void Piece::move(int posX, int posY)
{
	position[0] = posX;
	position[1] = posY;
}
