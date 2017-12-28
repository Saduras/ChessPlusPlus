#pragma once
#include "Agent.h"

class RandomAgent : public Agent
{
public:
	~RandomAgent();

	std::future<Move> nextTurn();
};