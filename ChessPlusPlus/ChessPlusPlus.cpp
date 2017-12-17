// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Game.h"
#include "ChessWindowView.h"

int main()
{
	Game game{};
	game.start();

	ChessWindowView view{ &game };
	view.run();

	return 0;
}

