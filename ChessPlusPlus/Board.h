#pragma once

#include "stdafx.h"
#include "Position.h"
#include "Pieces.h"
#include "Move.h"
#include <array>
#include <unordered_set>

class Board
{
public:
	~Board();

	void setupWithDefault();

	Piece* getPieceAt(Position pos);
	void placePieceAt(Piece *const piece, Position pos);

	bool isThreatenedBy(Position targetPos, Color playerColor);
	std::unordered_set<Move> getAllMovesFor(Color playerColor);

	void movePiece(Move move);
	void removePieceAt(Position pos);
	Board* testMove(Move move);

	void clear();

private:
	std::array<Piece*, 64> fields{};

	int getFieldIndex(Position pos);
};