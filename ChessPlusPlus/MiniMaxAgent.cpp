#include "stdafx.h"
#include "MiniMaxAgent.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <future>

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

#include <chrono>

class Timer
{
private:
	std::chrono::steady_clock::time_point start;
	std::string message;
public:
	Timer(const std::string& message)
		: message(message)
	{
		start = std::chrono::steady_clock::now();
	}

	~Timer()
	{
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << message << " elapsed time: " << elapsed_seconds.count() << "s\n";
	}
};

int callCounter = 0;

void MiniMaxAgent::selectMove(Board* board, std::vector<Move> moves)
{
	std::thread thread([this, board, moves]() 
	{
		Timer timer("Thinking time!");
		callCounter = 0;

		auto result = this->miniMaxSearch(this->searchDepth, this->color, true, board);
		this->handleResult(result);

		std::cout << "callCounter: " << callCounter << std::endl;
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

SearchResult MiniMaxAgent::miniMaxSearch_async(int searchDepth, Color currentPlayer, bool isMaximisingPlayer, Board* board)
{
	if (searchDepth == 0)
		return SearchResult{ evalFunc(board, color), Move{Position{-1,-1}, Position{-1,1} } };

	auto moves = game->getValidMoves(currentPlayer, board);
	std::shuffle(moves.begin(), moves.end(), generator);

	searchDepth--;
	auto nextPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
	int alpha = -10000;
	int beta = 10000;
	int bestScore = -9000;
	Move bestMove{};

	std::vector<std::future<SearchResult>> futures;
	std::vector<Board*> predictions(moves.size());

	// schedule searches for each move
	for (size_t i = 0; i < moves.size(); i++) {
		auto prediction = board->testMove(moves[i]);
		predictions.push_back(prediction);
		futures.push_back(
			std::async([searchDepth, nextPlayer, isMaximisingPlayer, prediction, alpha, beta, this]() 
				{ return this->miniMaxSearch(searchDepth, nextPlayer, !isMaximisingPlayer, prediction, alpha, beta); })
		);
	}

	// compare results of searches
	for (size_t i = 0; i < moves.size(); i++) {
		int moveScore = futures[i].get().score;

		if (isMaximisingPlayer && bestScore < moveScore
			|| !isMaximisingPlayer && bestScore > moveScore) {
			bestScore = moveScore;
			bestMove = moves[i];
		}

		delete predictions[i];
	}
	return SearchResult{ bestScore, bestMove };
}

SearchResult MiniMaxAgent::miniMaxSearch(int searchDepth, Color currentPlayer, bool isMaximisingPlayer, Board* board, int alpha, int beta)
{
	callCounter++;

	if (searchDepth == 0)
		return SearchResult{ evalFunc(board, color), Move{Position{-1,-1}, Position{-1,1} } };

	auto moves = game->getValidMoves(currentPlayer, board);
	std::shuffle(moves.begin(), moves.end(), generator);

	searchDepth--;
	auto nextPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;

	if (isMaximisingPlayer)
	{
		int bestScore = -9000;
		Move bestMove{};
		for (size_t i = 0; i < moves.size();  i++)
		{
			auto prediction = board->testMove(moves[i]);
			int moveScore = miniMaxSearch(searchDepth, nextPlayer, !isMaximisingPlayer, prediction, alpha, beta).score;
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
			int moveScore = miniMaxSearch(searchDepth, nextPlayer, !isMaximisingPlayer, prediction, alpha, beta).score;
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
