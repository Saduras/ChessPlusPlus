// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Board.h"
#include "Pieces/Pawn.h"
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

	view.print();

	system("pause");
	return 0;
}

