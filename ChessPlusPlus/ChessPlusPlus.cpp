// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Game.h"
#include "ChessWindowView.h"
#include "HumanAgent.h"
#include "RandomAgent.h"

int main()
{
	Game game{ new HumanAgent(), new RandomAgent() };
	game.start();

	ChessWindowView view{ &game };
	view.run();

	return 0;
}

