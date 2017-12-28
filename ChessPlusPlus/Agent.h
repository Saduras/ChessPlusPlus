#pragma once

#include "Game.h"
#include <future>

class Game;

class Agent
{
public:
	~Agent();

	inline void setup(Color color, Game *game) 
	{
		this->color = color;
		this->game = game;
	}
	virtual std::future<Move> nextTurn() = 0;
	std::vector<Move> getValidMoves(Color player, Board* board);

protected:
	Game* game;
	Color color;

	std::promise<Move> promise;
};