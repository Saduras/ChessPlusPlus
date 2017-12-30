#include "stdafx.h"
#include "MiniMaxAgent.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <chrono>

std::map<std::string, int> scoreMap{
	{ "K", 900 }, { "k", -900 },
	{ "Q", 90 },  { "q", -90 },
	{ "R", 50 },  { "e", -50 },
	{ "B", 30 },  { "b", -30 },
	{ "N", 30 },  { "n", -30 },
	{ "P", 10 },  { "p", -10 },
};

MiniMaxAgent::MiniMaxAgent(int searchDepth)
{
	this->searchDepth = searchDepth;
}

std::future<Move> MiniMaxAgent::nextTurn()
{
	promise = std::promise<Move>();

	auto board = game->getBoard();
	auto result = miniMaxSearch(searchDepth, color, true, board);

	std::cout << Move::toString(result.move) + " -> " + std::to_string(result.score) << std::endl;

	promise.set_value(result.move);
	return promise.get_future();
}

int MiniMaxAgent::evalBoard(Board* board)
{
	int score = 0;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			auto piece = board->getPieceAt(Position{ x, y });
			if (piece)
				score += scoreMap[piece->toShortString()];
		}
	}

	return score;
}

SearchResult MiniMaxAgent::miniMaxSearch(int searchDepth, Color currentPlayer, bool isMaximisingPlayer, Board* board, int alpha, int beta)
{
	if (searchDepth == 0)
		return SearchResult{ evalBoard(board), Move{Position{-1,-1},Position{-1,1} } };

	auto moves = game->getValidMoves(currentPlayer, board);
	std::random_shuffle(moves.begin(), moves.end());

	searchDepth--;
	auto nextPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;

	if (isMaximisingPlayer)
	{
		int bestScore = -9000;
		Move bestMove{};
		for (int i = 0; i < moves.size(); i++)
		{
			auto prediction = board->testMove(moves[i]);
			int moveScore = miniMaxSearch(searchDepth, nextPlayer, false, prediction, alpha, beta).score;
			delete prediction;

			if (bestScore < moveScore)
			{
				bestScore = moveScore;
				bestMove = moves[i];
			}

			alpha = std::max(bestScore, alpha);
			if (beta <= alpha)
				return SearchResult{ bestScore, bestMove };
		}
		return SearchResult{ bestScore, bestMove };
	}
	else
	{
		int bestScore = 9000;
		Move bestMove{};
		for (int i = 0; i < moves.size(); i++)
		{
			auto prediction = board->testMove(moves[i]);
			int moveScore = miniMaxSearch(searchDepth, nextPlayer, true, prediction, alpha, beta).score;
			delete prediction;

			if (bestScore > moveScore)
			{
				bestScore = moveScore;
				bestMove = moves[i];
			}

			beta = std::min(bestScore, beta);
			if (beta <= alpha)
				return SearchResult{ bestScore, bestMove };
		}
		return SearchResult{ bestScore, bestMove };
	}
}
