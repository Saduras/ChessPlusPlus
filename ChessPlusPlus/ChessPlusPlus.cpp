// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Game.h"
#include "ChessWindowView.h"
#include "HumanAgent.h"
#include "RandomAgent.h"
#include "MiniMaxAgent.h"

int main()
{
	Game game{ 
		new MiniMaxAgent{ 4, MiniMaxAgent::pieceValueEvalBoard }, 
		new MiniMaxAgent{ 4, MiniMaxAgent::pieceValueEvalBoard }, 
		0 // delay in ms
	};
	game.start();

	ChessWindowView view{ &game };
	view.run();

	return 0;
}

