#pragma once

#include "Game.h"

class Game;

class Agent
{
public:
	inline void setGame(Game *game) { this->game = game; }
	virtual void nextTurn() = 0;

protected:
	Game* game;
};