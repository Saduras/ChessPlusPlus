#include "stdafx.h"
#include "MiniMaxAgent.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

std::map<std::string, int> scoreMap{
	{ "K", 900 }, { "k", -900 },
	{ "Q", 90 },  { "q", -90 },
	{ "R", 50 },  { "e", -50 },
	{ "B", 30 },  { "b", -30 },
	{ "N", 30 },  { "n", -30 },
	{ "P", 10 },  { "p", -10 },
};

MiniMaxAgent::MiniMaxAgent(int searchDepth, std::function<int(Board*, Color)> evalFunc)
{
	this->searchDepth = searchDepth;
	this->evalFunc = evalFunc;

	std::random_device r;
	std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
	generator = std::mt19937{ seed };
}

void MiniMaxAgent::selectMove(Board* board, std::vector<Move> moves)
{
	std::thread thread([this, board, moves]() 
	{
		auto result = this->miniMaxSearch(this->searchDepth, this->color, true, board);
		this->handleResult(result);
	});
	thread.detach();
}

void MiniMaxAgent::handleResult(SearchResult result)
{
	std::cout << Move::toString(result.move) + " -> " + std::to_string(result.score) << std::endl;
	game->doMove(result.move);
}

int MiniMaxAgent::pieceValueEvalBoard(Board* board, Color color)
{
	int colorFactor = color == Color::WHITE ? 1 : -1;

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

	return score * colorFactor;
}

SearchResult MiniMaxAgent::miniMaxSearch(int searchDepth, Color currentPlayer, bool isMaximisingPlayer, Board* board, int alpha, int beta)
{
	if (searchDepth == 0)
		return SearchResult{ evalFunc(board, color), Move{Position{-1,-1},Position{-1,1} } };

	auto moves = game->getValidMoves(currentPlayer, board);
	std::shuffle(moves.begin(), moves.end(), generator);

	searchDepth--;
	auto nextPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;

	if (isMaximisingPlayer)
	{
		int bestScore = -9000;
		Move bestMove{};
		for (size_t i = 0; i < moves.size(); i++)
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
		for (size_t i = 0; i < moves.size(); i++)
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
