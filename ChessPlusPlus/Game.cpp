#include "stdafx.h"
#include "Game.h" 

Game::Game(Agent *whiteAgent, Agent *blackAgent)
{
	this->whiteAgent = whiteAgent;
	whiteAgent->setGame(this);
	this->blackAgent = blackAgent;
	blackAgent->setGame(this);
}

Game::~Game()
{
	delete whiteAgent;
	delete blackAgent;
}

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

void Game::restart()
{
	board.clear();
	state = GameState::UNSTARTED;
	system("cls");

	this->start();
}

bool isRunning(Game *game)
{
	return game->getState() == GameState::ONGOING 
		|| game->getState() == GameState::CHECK_WHITE 
		|| game->getState() == GameState::CHECK_BLACK;
}

bool Game::isValidMove(Move move)
{
	bool isValidPieceMove = false;
	Piece *piece = board.getPieceAt(move.from);
	Color opponentColor = currentPlayer == Color::WHITE ? Color::BLACK : Color::WHITE;

	if (piece && piece->getColor() == currentPlayer)
		isValidPieceMove = piece->isValidMove(move, board);
	
	bool willBeCheck = false;
	if (isValidPieceMove)
	{
		auto prediction = board.testMove(move);
		willBeCheck = isCheck_internal(currentPlayer, prediction);
		delete prediction;
	}
	return isValidPieceMove && !willBeCheck;
}

bool Game::doMove(Move move)
{
	if (!isRunning(this))
		return false;

	if (!isValidMove(move))
		return false;

	Piece *toRemove = board.getPieceAt(move.to);
	if (toRemove)
	{
		if (onRemovePiece)
			onRemovePiece(toRemove);
		board.removePieceAt(move.to);
	}
	delete toRemove;

	Piece *toMove = board.getPieceAt(move.from);
	if (onMovePiece)
		onMovePiece(toMove, move.to);
	board.movePiece(move);

	currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
	getCurrentAgent()->nextTurn();

	if (isCheckmate(currentPlayer))
	{
		state = (currentPlayer == Color::WHITE) ? GameState::CHECKMATE_WHITE : GameState::CHECKMATE_BLACK;
		std::cout << ((currentPlayer == Color::WHITE) ? "Black wins!" : "White wins!") << std::endl;
		std::cout << "Press enter to restart game." << std::endl;
	}
	return true;
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

bool Game::isCheck_internal(Color playerColor, Board *board)
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