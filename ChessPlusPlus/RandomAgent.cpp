#include "stdafx.h"
#include "RandomAgent.h"
#include <vector>
#include <algorithm>

void RandomAgent::nextTurn()
{
	auto movesSet = game->getBoard()->getAllMovesFor(color);

	std::vector<Move> movesVector{ movesSet.size() };
	for (auto move = movesSet.begin(); move != movesSet.end(); move++)
		movesVector.push_back(*move);

	std::random_shuffle(movesVector.begin(), movesVector.end());

	for (int i = 0; i < movesVector.size(); i++)
		if (game->doMove(movesVector[i]))
			return;
}