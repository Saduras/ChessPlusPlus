#pragma once

#include <functional>
#include "Board.h"
#include "Piece.h"

enum class GameState
{
	UNSTARTED,
	ONGOING,
	CHECK_WHITE,
	CHECKMATE_WHITE,
	CHECK_BLACK,
	CHECKMATE_BLACK,
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
	void restart();
	bool doMove(Move move);

	bool isValidMove(Move move);
	bool isCheck(Color playerColor);
	bool isCheckmate(Color playerColor);

private:
	GameState state{ GameState::UNSTARTED };
	Board board{};
	Color currentPlayer;

	std::function<void(Piece*)> onRemovePiece;
	std::function<void(Piece*, Position)> onMovePiece;

	bool isCheck_internal(Color currentPlayer, Board *board);
};