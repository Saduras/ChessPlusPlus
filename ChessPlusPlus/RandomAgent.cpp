#include "stdafx.h"
#include "RandomAgent.h"
#include <vector>
#include <algorithm>

std::future<Move> RandomAgent::nextTurn()
{
	promise = std::promise<Move>{};
	
	auto moves = getValidMoves(color, game->getBoard());
	std::random_shuffle(moves.begin(), moves.end());

	promise.set_value(moves[0]);
	return promise.get_future();
}