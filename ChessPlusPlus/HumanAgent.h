#pragma once
#include "Agent.h"

class HumanAgent : public Agent
{
public:
	void selectMove(Board* board, std::vector<Move> move);
	void chooseMove(Move move);
};

