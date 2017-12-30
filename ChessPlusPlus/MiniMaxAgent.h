#pragma once
#include "Agent.h"
#include <random>

struct SearchResult
{
	int score;
	Move move;
};

class MiniMaxAgent : public Agent
{
public:
	MiniMaxAgent(int searchDepth);
	std::future<Move> nextTurn();

	int evalBoard(Board* board);
	SearchResult miniMaxSearch(int searchDepth, Color currentPlayer, bool isMaximisingPlayer, Board *board, int alpha = -10000, int beta = 10000);

private:
	int searchDepth;
	std::mt19937 generator;
};