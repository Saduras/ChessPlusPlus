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

bool isRunning(Game *game)
{
	return game->getState() == GameState::ONGOING 
		|| game->getState() == GameState::CHECK_WHITE 
		|| game->getState() == GameState::CHECK_BLACK;
}

bool Game::doMove(Position from, Position to)
{
	bool isValid = board.isValidMove(from, to, currentPlayer);
	if (isValid && isRunning(this))
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

		if (isCheck(currentPlayer))
		{
			std::cout << "moved into check. Invalid!" << std::endl;
			// revert move
			board.movePiece(to, from);
			if (toRemove)
				board.placePieceAt(toRemove, to);
		}
		else
		{
			delete toRemove;
			currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;

			if (isCheckmate(currentPlayer))
			{
				state = (currentPlayer == Color::WHITE) ? GameState::CHECKMATE_WHITE : GameState::CHECKMATE_BLACK;
				std::cout << ((currentPlayer == Color::WHITE) ? "Black wins!" : "White wins!") << std::endl;
			}
		}
	}
	return isValid;
}

Position findKing(Board *board, const Color playerColor)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Position pos{ x, y };
			auto piece = board->getPieceAt(pos);
			if (dynamic_cast<King*>(piece) && piece->getColor() == playerColor)
			{
				return pos;
			}
		}
	}
	return Position{ -1, -1 };
}

bool isCheck_internal(Color playerColor, Board *board)
{
	Position kingPos = findKing(board, playerColor);
	Color opponentColor = playerColor == Color::WHITE ? Color::BLACK : Color::WHITE;

	return board->isThreatenedBy(kingPos, opponentColor);
}

bool Game::isCheck(Color playerColor)
{
	return isCheck_internal(playerColor, &board);
}

bool Game::isCheckmate(Color playerColor)
{
	bool result = false;
	bool isCheck = this->isCheck(playerColor);

	if (isCheck)
	{
		auto moves = board.getAllMovesFor(playerColor);
		bool hasValidMove = false;
		for (auto move : moves)
		{
			Board *prediction = board.testMove(move);
			hasValidMove |= !isCheck_internal(playerColor, prediction);
			delete prediction;
		}

		result = isCheck && !hasValidMove;
	}

	return result;
}