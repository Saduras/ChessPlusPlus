#pragma once

#include "Game.h"

class Game;

class Agent
{
public:
	inline void setup(Color color, Game *game) 
	{
		this->color = color;
		this->game = game;
	}
	virtual void nextTurn() = 0;

protected:
	Game* game;
	Color color;
};