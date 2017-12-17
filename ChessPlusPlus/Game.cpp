#include "stdafx.h"
#include "Game.h" 

void Game::start()
{
	if (state != GameState::UNSTARTED)
	{
		return;
	}

	state = GameState::ONGOING;
	board = Board{};
	board.setupWithDefault();

	currentPlayer = Color::WHITE;
}

bool Game::doMove(Position from, Position to)
{
	bool isValid = board.isValidMove(from, to, currentPlayer);
	if (isValid && state == GameState::ONGOING)
	{
		board.movePiece(from, to);
		currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
	}
	return isValid;
}