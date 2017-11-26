#include "stdafx.h"
#include "Board.h"

// public

// constructor
Board::Board()
{
	// Standard setup
	this->placePieceAt(new Rook   { 0,0, Color::WHITE }, 0, 0);
	this->placePieceAt(new Knight { 1,0, Color::WHITE }, 1, 0);
	this->placePieceAt(new Bishop { 2,0, Color::WHITE }, 2, 0);
	this->placePieceAt(new Queen  { 3,0, Color::WHITE }, 3, 0);
	this->placePieceAt(new King   { 4,0, Color::WHITE }, 4, 0);
	this->placePieceAt(new Bishop { 5,0, Color::WHITE }, 5, 0);
	this->placePieceAt(new Knight { 6,0, Color::WHITE }, 6, 0);
	this->placePieceAt(new Rook   { 7,0, Color::WHITE }, 7, 0);

	this->placePieceAt(new Rook   { 0,7, Color::BLACK }, 0, 7);
	this->placePieceAt(new Knight { 1,7, Color::BLACK }, 1, 7);
	this->placePieceAt(new Bishop { 2,7, Color::BLACK }, 2, 7);
	this->placePieceAt(new Queen  { 3,7, Color::BLACK }, 3, 7);
	this->placePieceAt(new King   { 4,7, Color::BLACK }, 4, 7);
	this->placePieceAt(new Bishop { 5,7, Color::BLACK }, 5, 7);
	this->placePieceAt(new Knight { 6,7, Color::BLACK }, 6, 7);
	this->placePieceAt(new Rook   { 7,7, Color::BLACK }, 7, 7);

	for (int x = 0; x < 8; x++)
	{
		this->placePieceAt(new Pawn{ x, 1, Color::WHITE }, x, 1);
		this->placePieceAt(new Pawn{ x, 6, Color::BLACK }, x, 6);
	}
}

// destructor
Board::~Board()
{
	for (int i = 0; i < fields.size(); i++)
		if (fields[i])
		{
			delete fields[i];
			fields[i] = nullptr;
		}
			
}

Piece* Board::getPieceAt(int x, int y)
{
	return fields.at(getFieldIndex(x, y));
}

void Board::placePieceAt(Piece *const piece, int x, int y)
{
	fields[getFieldIndex(x, y)] = piece;
}

bool Board::movePiece(int fromX, int fromY, int toX, int toY)
{
	Piece *piece = getPieceAt(fromX, fromY);

	if (piece)
	{
		// destroy piece at target field
		int targetIndex = getFieldIndex(toX, toY);
		if (fields[targetIndex])
			delete fields[targetIndex];
		// move piece
		fields[getFieldIndex(fromX, fromY)] = nullptr;
		fields[targetIndex] = piece;
		return true;
	}
	else
		return false;
}

// private
std::array<Piece*, 64> Board::fields{};

int Board::getFieldIndex(int x, int y)
{
	return x + y * 8;
}
