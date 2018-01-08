#pragma once
#include "Agent.h"
#include <random>

class RandomAgent : public Agent
{
public:
	RandomAgent();

	void selectMove(Board* board, std::vector<Move> moves);

private:
	std::mt19937 generator;
};