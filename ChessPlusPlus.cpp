// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Pawn.h"

using namespace std;

int main()
{
	Pawn pawn(2, 3, black);

	cout << pawn.toString() << endl;
	cout << pawn.isValidMove(2, 2, none) << endl;
	pawn.move(2, 2);
	cout << pawn.toString() << endl;

	system("pause");
    return 0;
}

