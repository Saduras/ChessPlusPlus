#pragma once

#include "Position.h"
#include "Move.h"
#include <vector>

class Board;

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

	bool isValidMove(Move move, Board &board);
	virtual std::vector<Position> getMovesFor(Position startPos, Board &board) = 0;
	virtual std::vector<Position> getThreatedFieldsFor(Position startPos, Board &board) = 0;

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

	virtual Piece* clone() = 0;

	virtual std::string toString() = 0;
	virtual std::string toShortString() = 0;

private:
	Color color;
};