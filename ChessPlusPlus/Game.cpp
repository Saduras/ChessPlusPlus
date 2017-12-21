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
			if (onRemovePiece)
				onRemovePiece(toRemove);
			board.removePieceAt(to);
		}

		Piece *toMove = board.getPieceAt(from);
		if (onMovePiece)
			onMovePiece(toMove, to);
		board.movePiece(from, to);

		currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
	}
	return isValid;
}

Position findKing(Board &board, const Color playerColor)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Position pos{ x, y };
			auto piece = board.getPieceAt(pos);
			if (dynamic_cast<King*>(piece) && piece->getColor() == playerColor)
			{
				return pos;
			}
		}
	}
	return Position{ -1, -1 };
}

bool Game::isCheck(Color playerColor)
{
	Position kingPos = findKing(board, playerColor);
	Color opponentColor = playerColor == Color::WHITE ? Color::BLACK : Color::WHITE;

	return board.isThreatenedBy(kingPos, opponentColor);
}

bool Game::isCheckmate(Color playerColor)
{
	Position kingPos = findKing(board, playerColor);
	Color opponentColor = playerColor == Color::WHITE ? Color::BLACK : Color::WHITE;

	bool isCheck = board.isThreatenedBy(kingPos, opponentColor);

	bool hasValidMove = false;
	auto moves = board.getPieceAt(kingPos)->getMovesFor(kingPos, board);
	for (auto move : moves)
		hasValidMove |= !board.isThreatenedBy(move, opponentColor);

	return isCheck && !hasValidMove;
}