#pragma once

#include <functional>
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
	inline Board* getBoard() { return &board; }

	inline void setCallbacks(std::function<void(Piece*)> onRemovePiece, std::function<void(Piece*, Position)> onMovePiece)
	{
		this->onRemovePiece = onRemovePiece;
		this->onMovePiece = onMovePiece;
	}
	void start();
	bool doMove(Position from, Position to);

private:
	GameState state{ GameState::UNSTARTED };
	Board board{};
	Color currentPlayer;

	std::function<void(Piece*)> onRemovePiece;
	std::function<void(Piece*, Position)> onMovePiece;
};