#include "stdafx.h"
#include "RandomAgent.h"
#include <vector>
#include <algorithm>

RandomAgent::RandomAgent()
{
	std::random_device r;
	std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
	generator = std::mt19937{ seed };
}

void RandomAgent::selectMove(Board* board, std::vector<Move> moves)
{
	std::shuffle(moves.begin(), moves.end(), generator);
	game->doMove(moves[0]);
}