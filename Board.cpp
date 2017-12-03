#include "stdafx.h"
#include "Board.h"

// public

// constructor
Board::Board()
{
	// Standard setup
	this->placePieceAt(new Rook   { 0,0, Color::WHITE }, Position{ 0, 0 });
	this->placePieceAt(new Knight { 1,0, Color::WHITE }, Position{ 1, 0 });
	this->placePieceAt(new Bishop { 2,0, Color::WHITE }, Position{ 2, 0 });
	this->placePieceAt(new Queen  { 3,0, Color::WHITE }, Position{ 3, 0 });
	this->placePieceAt(new King   { 4,0, Color::WHITE }, Position{ 4, 0 });
	this->placePieceAt(new Bishop { 5,0, Color::WHITE }, Position{ 5, 0 });
	this->placePieceAt(new Knight { 6,0, Color::WHITE }, Position{ 6, 0 });
	this->placePieceAt(new Rook   { 7,0, Color::WHITE }, Position{ 7, 0 });
														 			    
	this->placePieceAt(new Rook   { 0,7, Color::BLACK }, Position{ 0, 7 });
	this->placePieceAt(new Knight { 1,7, Color::BLACK }, Position{ 1, 7 });
	this->placePieceAt(new Bishop { 2,7, Color::BLACK }, Position{ 2, 7 });
	this->placePieceAt(new Queen  { 3,7, Color::BLACK }, Position{ 3, 7 });
	this->placePieceAt(new King   { 4,7, Color::BLACK }, Position{ 4, 7 });
	this->placePieceAt(new Bishop { 5,7, Color::BLACK }, Position{ 5, 7 });
	this->placePieceAt(new Knight { 6,7, Color::BLACK }, Position{ 6, 7 });
	this->placePieceAt(new Rook   { 7,7, Color::BLACK }, Position{ 7, 7 });

	for (int x = 0; x < 8; x++)
	{
		this->placePieceAt(new Pawn{ x, 1, Color::WHITE }, Position{ x, 1 });
		this->placePieceAt(new Pawn{ x, 6, Color::BLACK }, Position{ x, 6 });
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

Piece* Board::getPieceAt(Position pos)
{
	return fields.at(getFieldIndex(pos));
}

void Board::placePieceAt(Piece *const piece, Position pos)
{
	fields[getFieldIndex(pos)] = piece;
}

bool Board::movePiece(Position from, Position to)
{
	Piece *piece = getPieceAt(from);

	if (piece)
	{
		// destroy piece at target field
		int targetIndex = getFieldIndex(to);
		if (fields[targetIndex])
			delete fields[targetIndex];
		// move piece
		fields[getFieldIndex(from)] = nullptr;
		fields[targetIndex] = piece;
		return true;
	}
	else
		return false;
}

// private
std::array<Piece*, 64> Board::fields{};

int Board::getFieldIndex(Position pos)
{
	return pos.x + pos.y * 8;
}
