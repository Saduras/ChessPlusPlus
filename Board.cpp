#include "stdafx.h"
#include "Board.h"

// public

// constructor
Board::Board()
{
	this->placePieceAt(new Rook   { 0,0, Color::white }, 0, 0);
	this->placePieceAt(new Knight { 1,0, Color::white }, 1, 0);
	this->placePieceAt(new Bishop { 2,0, Color::white }, 2, 0);
	this->placePieceAt(new Queen  { 3,0, Color::white }, 3, 0);
	this->placePieceAt(new King   { 4,0, Color::white }, 4, 0);
	this->placePieceAt(new Bishop { 5,0, Color::white }, 5, 0);
	this->placePieceAt(new Knight { 6,0, Color::white }, 6, 0);
	this->placePieceAt(new Rook   { 7,0, Color::white }, 7, 0);

	this->placePieceAt(new Rook   { 0,7, Color::black }, 0, 7);
	this->placePieceAt(new Knight { 1,7, Color::black }, 1, 7);
	this->placePieceAt(new Bishop { 2,7, Color::black }, 2, 7);
	this->placePieceAt(new Queen  { 3,7, Color::black }, 3, 7);
	this->placePieceAt(new King   { 4,7, Color::black }, 4, 7);
	this->placePieceAt(new Bishop { 5,7, Color::black }, 5, 7);
	this->placePieceAt(new Knight { 6,7, Color::black }, 6, 7);
	this->placePieceAt(new Rook   { 7,7, Color::black }, 7, 7);

	for (int x = 0; x < 8; x++)
	{
		this->placePieceAt(new Pawn{ x, 1, Color::white }, x, 1);
		this->placePieceAt(new Pawn{ x, 6, Color::black }, x, 6);
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

// private
std::array<Piece*, 64> Board::fields{};

int Board::getFieldIndex(int x, int y)
{
	return x + y * 8;
}
