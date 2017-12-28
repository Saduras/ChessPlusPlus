#pragma once
#include "Agent.h"

class RandomAgent : public Agent
{
public:
	std::future<Move> nextTurn();
};