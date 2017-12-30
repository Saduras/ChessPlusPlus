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

std::future<Move> RandomAgent::nextTurn()
{
	promise = std::promise<Move>{};
	
	auto moves = game->getValidMoves(color, game->getBoard());
	std::shuffle(moves.begin(), moves.end(), generator);

	promise.set_value(moves[0]);
	return promise.get_future();
}