#pragma once

#include "Board.h"
#include "Piece.h"

enum class GameState
{
	UNSTARTED,
	ONGOING,
	WON_WHITE,
	WON_BLACK,
};

class Game
{
public:
	inline GameState getState() { return state; }
	inline Board getBoard() { 
		board.getPieceAt(Position{ 0,0 });
		return board; 
	}

	void start();
	bool doMove(Position from, Position to);

private:
	GameState state{ GameState::UNSTARTED };
	Board board;
	Color currentPlayer;
};