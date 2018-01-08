#include "stdafx.h"
#include "HumanAgent.h"

void HumanAgent::selectMove(Board* board, std::vector<Move> moves)
{
	// wait for move to be selected
}

void HumanAgent::chooseMove(Move move)
{
	game->doMove(move);
}