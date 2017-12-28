#pragma once
#include "Agent.h"

class HumanAgent : public Agent
{
public:
	~HumanAgent();

	std::future<Move> nextTurn();
	inline void setMove(Move move) { promise.set_value(move); };
};

