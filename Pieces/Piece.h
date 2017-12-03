#pragma once

#include "Position.h"
#include <vector>

enum Color
{
	NONE,
	WHITE,
	BLACK,
};

class Piece
{
public:
	explicit Piece(Color color);

	bool isValidMove(Position from, Position to);
	virtual std::vector<Position> getMovesFor(Position startPos) = 0;

	inline Color getColor() { return color; }
	inline std::string getColorString() {
		switch (color)
		{
		case NONE:
			return "none";
		case WHITE:
			return "white";
		case BLACK:
			return "black";
		default:
			return "unkown";
		}
	}

	virtual std::string toString() = 0;
	virtual std::string toShortString() = 0;

private:
	Color color;
};