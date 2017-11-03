#include "stdafx.h"
#include "Piece.h"

Piece::Piece(int posX, int posY, Color col)
{
	position[0] = posX;
	position[1] = posY;
	color = col;
}