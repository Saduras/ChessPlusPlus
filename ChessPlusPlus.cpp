// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Board.h"
#include "Pawn.h"
#include "ChessConsoleView.h"

using namespace std;

void printPiece(Piece piece)
{
	std::cout << piece.toShortString();
}

int main()
{
	Board board{};
	ChessConsoleView view{ board };

	//view.print();

	//std::cout << "\n";

	for (int x = 0; x < 8; x++)
	{
		Pawn whitePawn{ x, 1, Color::white };
		board.placePieceAt(&whitePawn, x, 1);

		Pawn blackPawn{ x, 6, Color::black };
		board.placePieceAt(&blackPawn, x, 6);
	}

	view.print();

	system("pause");
	return 0;
}

