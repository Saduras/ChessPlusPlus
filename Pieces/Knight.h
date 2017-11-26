#pragma once

#include "Piece.h"
#include <string>

class Knight : public Piece
{
public:
	using Piece::Piece;

	bool isValidMove(int posX, int posY, Color owner);

	std::string toString();
	std::string toShortString();
};