#pragma once
#include "Agent.h"
#include <random>

class RandomAgent : public Agent
{
public:
	RandomAgent();

	std::future<Move> nextTurn();

private:
	std::mt19937 generator;
};