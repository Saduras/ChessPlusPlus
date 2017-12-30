#pragma once
#include "Agent.h"
#include <functional>
#include <random>

struct SearchResult
{
	int score;
	Move move;
};

class MiniMaxAgent : public Agent
{
public:
	MiniMaxAgent(int searchDepth, std::function<int(Board*, Color)> evalFunc);
	std::future<Move> nextTurn();

	static int pieceValueEvalBoard(Board* board, Color color);
	SearchResult miniMaxSearch(int searchDepth, Color currentPlayer, bool isMaximisingPlayer, Board *board, int alpha = -10000, int beta = 10000);

private:
	int searchDepth;
	std::function<int(Board*, Color)> evalFunc;
	std::mt19937 generator;
};