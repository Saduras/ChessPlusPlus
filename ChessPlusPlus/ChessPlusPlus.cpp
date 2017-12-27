// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Game.h"
#include "ChessWindowView.h"
#include "HumanAgent.h"

int main()
{
	Game game{ new HumanAgent(), new HumanAgent() };
	game.start();

	ChessWindowView view{ &game };
	view.run();

	return 0;
}

