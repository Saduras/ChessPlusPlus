#include "stdafx.h"
#include "Game.h" 

void Game::start()
{
	if (state != GameState::UNSTARTED)
	{
		return;
	}

	state = GameState::ONGOING;
	board.setupWithDefault();

	currentPlayer = Color::WHITE;
}

bool Game::doMove(Position from, Position to)
{
	bool isValid = board.isValidMove(from, to, currentPlayer);
	if (isValid && state == GameState::ONGOING)
	{
		Piece *toRemove = board.getPieceAt(to);
		if (toRemove)
		{
			if(onRemovePiece)
				onRemovePiece(toRemove);
			board.removePiece(to);
		}

		Piece *toMove = board.getPieceAt(from);
		if(onMovePiece)
			onMovePiece(toMove, to);
		board.movePiece(from, to);

		currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
	}
	return isValid;
}