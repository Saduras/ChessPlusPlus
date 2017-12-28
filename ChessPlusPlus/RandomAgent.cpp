#include "stdafx.h"
#include "RandomAgent.h"
#include <vector>
#include <algorithm>

RandomAgent::~RandomAgent()
{
	promise.set_value(Move{});
}

std::future<Move> RandomAgent::nextTurn()
{
	auto movesSet = game->getBoard()->getAllMovesFor(color);

	std::vector<Move> movesVector{ movesSet.size() };
	for (auto move = movesSet.begin(); move != movesSet.end(); move++)
		movesVector.push_back(*move);

	std::random_shuffle(movesVector.begin(), movesVector.end());

	promise = std::promise<Move>{};

	for (int i = 0; i < movesVector.size(); i++)
		if (game->isValidMove(movesVector[i]))
		{
			promise.set_value(movesVector[i]);
			return promise.get_future();
		}
}