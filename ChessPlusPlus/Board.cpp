#include "stdafx.h"
#include "Board.h"

// public
Board::~Board()
{
	clear();
}

void Board::setupWithDefault()
{
	// Standard setup
	this->placePieceAt(new Rook{ Color::WHITE }, Position{ 0, 0 });
	this->placePieceAt(new Knight{ Color::WHITE }, Position{ 1, 0 });
	this->placePieceAt(new Bishop{ Color::WHITE }, Position{ 2, 0 });
	this->placePieceAt(new Queen{ Color::WHITE }, Position{ 3, 0 });
	this->placePieceAt(new King{ Color::WHITE }, Position{ 4, 0 });
	this->placePieceAt(new Bishop{ Color::WHITE }, Position{ 5, 0 });
	this->placePieceAt(new Knight{ Color::WHITE }, Position{ 6, 0 });
	this->placePieceAt(new Rook{ Color::WHITE }, Position{ 7, 0 });

	this->placePieceAt(new Rook{ Color::BLACK }, Position{ 0, 7 });
	this->placePieceAt(new Knight{ Color::BLACK }, Position{ 1, 7 });
	this->placePieceAt(new Bishop{ Color::BLACK }, Position{ 2, 7 });
	this->placePieceAt(new Queen{ Color::BLACK }, Position{ 3, 7 });
	this->placePieceAt(new King{ Color::BLACK }, Position{ 4, 7 });
	this->placePieceAt(new Bishop{ Color::BLACK }, Position{ 5, 7 });
	this->placePieceAt(new Knight{ Color::BLACK }, Position{ 6, 7 });
	this->placePieceAt(new Rook{ Color::BLACK }, Position{ 7, 7 });

	for (int x = 0; x < 8; x++)
	{
		this->placePieceAt(new Pawn{ Color::WHITE }, Position{ x, 1 });
		this->placePieceAt(new Pawn{ Color::BLACK }, Position{ x, 6 });
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

bool Board::isThreatenedBy(Position targetPos, Color playerColor)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Position pos{ x, y };
			auto piece = getPieceAt(pos);
			if (piece && piece->getColor() == playerColor)
			{
				auto moves = piece->getThreatedFieldsFor(pos, *this);
				if (std::find(moves.begin(), moves.end(), targetPos) != moves.end())
				{
					return true;
				}
			}
		}
	}
	return false;
}

std::unordered_set<Move> Board::getAllMovesFor(Color playerColor)
{
	std::unordered_set<Move> moves{};

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Position pos{ x,y };
			auto piece = getPieceAt(pos);
			if (piece && piece->getColor() == playerColor)
			{
				auto targetFields = piece->getMovesFor(pos, *this);
				for (Position targetPos : targetFields)
				{
					bool equal = Move{ Position{0,0}, Position{1,1}} == Move{ pos, targetPos };
					
					moves.insert(Move{ pos, targetPos });
				}
			}
		}
	}

	return moves;
}

void Board::movePiece(Move move)
{
	Piece *piece = getPieceAt(move.from);
	fields[getFieldIndex(move.from)] = nullptr;
	fields[getFieldIndex(move.to)] = piece;
}

void Board::removePieceAt(Position pos)
{
	int targetIndex = getFieldIndex(pos);
	if (fields[targetIndex])
		fields[targetIndex] = nullptr;
}

Board* Board::testMove(Move move)
{
	Board *copy = new Board{};

	for (size_t i = 0; i < copy->fields.size(); i++)
	{
		if (this->fields[i])
			copy->fields[i] = this->fields[i]->clone();
		else
			copy->fields[i] = nullptr;
	}

	copy->movePiece(move);
	return copy;
}

void Board::clear()
{
	for (unsigned int i = 0; i < fields.size(); i++)
		if (fields[i])
		{
			delete fields[i];
			fields[i] = nullptr;
		}
}

// private
int Board::getFieldIndex(Position pos)
{
	return pos.x + pos.y * 8;
}

