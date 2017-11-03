#pragma once

enum Color
{
	white,
	black,
};


class Piece
{
public:
	explicit Piece(int posX, int posY, Color col);

	int* getPosition() { return position; }
	Color getColor() { return color; }

private:
	int position[2];
	Color color;
};