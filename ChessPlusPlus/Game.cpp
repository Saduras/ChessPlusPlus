#include "stdafx.h"
#include "Game.h" 
#include <chrono>

Game::Game(Agent *whiteAgent, Agent *blackAgent, int delayInMs)
{
	moveDelayInMs = delayInMs;
	this->whiteAgent = whiteAgent;
	whiteAgent->setup(Color::WHITE, this);
	this->blackAgent = blackAgent;
	blackAgent->setup(Color::BLACK, this);
}

Game::~Game()
{
	delete whiteAgent;
	delete blackAgent;
	if (isRunning())
		stop();
}

void Game::start()
{
	if (state != GameState::UNSTARTED)
		return;

	state = GameState::ONGOING;
	board.setupWithDefault();

	currentPlayer = Color::WHITE;
	
	getCurrentAgent()->selectMove(getBoard(), getValidMoves(currentPlayer, &board));
}

void Game::restart()
{
	stop();
	start();
}

void Game::stop()
{
	board.clear();
	state = GameState::UNSTARTED;
	system("cls");
}

bool Game::isRunning()
{
	return this->getState() == GameState::ONGOING 
		|| this->getState() == GameState::CHECK_WHITE 
		|| this->getState() == GameState::CHECK_BLACK;
}

bool Game::isValidMove(Move move, Color playerColor, Board *board)
{
	bool isValidPieceMove = false;
	Piece *piece = board->getPieceAt(move.from);
	Color opponentColor = currentPlayer == Color::WHITE ? Color::BLACK : Color::WHITE;

	if (piece && piece->getColor() == playerColor)
		isValidPieceMove = piece->isValidMove(move, *board);
	
	bool willBeCheck = false;
	if (isValidPieceMove)
	{
		auto prediction = board->testMove(move);
		willBeCheck = isCheck_internal(currentPlayer, prediction);
		delete prediction;
	}
	return isValidPieceMove && !willBeCheck;
}

bool Game::doMove(Move move)
{
	if (!isRunning())
		return false;

	if (!isValidMove(move, currentPlayer, &board))
	{
		getCurrentAgent()->selectMove(getBoard(), getValidMoves(currentPlayer, &board));
		return false;
	}

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

	if (isCheckmate(currentPlayer))
	{
		state = (currentPlayer == Color::WHITE) ? GameState::CHECKMATE_WHITE : GameState::CHECKMATE_BLACK;
		std::cout << ((currentPlayer == Color::WHITE) ? "Black wins!" : "White wins!") << std::endl;
		std::cout << "Press enter to restart game." << std::endl;
	}
	else
	{
		getCurrentAgent()->selectMove(getBoard(), getValidMoves(currentPlayer, &board));
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
	auto moves = getValidMoves(playerColor, getBoard());
	return moves.size() == 0;
}

std::vector<Move> Game::getValidMoves(Color player, Board* board)
{
	auto movesSet = board->getAllMovesFor(player);

	std::vector<Move> movesVector{};
	for (auto move = movesSet.begin(); move != movesSet.end(); move++)
		if (this->isValidMove(*move, player, board))
			movesVector.push_back(*move);

	return movesVector;
}