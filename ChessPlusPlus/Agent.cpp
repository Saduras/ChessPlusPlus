#include "stdafx.h"
#include "Agent.h"

Agent::~Agent()
{
	promise.set_value(Move{});
}

std::vector<Move> Agent::getValidMoves(Color player, Board* board)
{
	auto movesSet = board->getAllMovesFor(player);

	std::vector<Move> movesVector{};
	for (auto move = movesSet.begin(); move != movesSet.end(); move++)
		if (this->game->isValidMove(*move, player, board))
			movesVector.push_back(*move);

	return movesVector;
}