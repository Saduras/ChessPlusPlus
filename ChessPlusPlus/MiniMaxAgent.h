#pragma once
#include "Agent.h"

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
};