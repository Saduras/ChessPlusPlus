#pragma once

#include "stdafx.h"

enum Color
{
	none,
	white,
	black,
};

class Piece
{
public:
	explicit Piece(int posX, int posY, Color col);

	virtual bool isValidMove(int posX, int posY, Color owner) { return false; }
	void move(int posX, int posY);

	inline int* getPosition() { return position; }
	inline std::string getPositonString()
	{
		return std::string(1,(char) ((int)'a' + position[0])) 
			+ std::to_string(position[1] + 1);
	}

	inline Color getColor() { return color; }
	inline std::string getColorString() {
		switch (color)
		{
		case none:
			return "none";
		case white:
			return "white";
		case black:
			return "black";
		default:
			return "unkown";
		}
	}

	virtual std::string toString() { return "??"; }
	virtual std::string toShortString() { return "??"; }

protected:
	bool isOnBoard(int posX, int posY);

private:
	int position[2];
	Color color;
};